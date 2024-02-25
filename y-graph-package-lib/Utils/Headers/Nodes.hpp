#ifndef Y_GRAPH_NODES_HPP
#define Y_GRAPH_NODES_HPP

#include <memory>
#include <set>
#include <string>
#include <vector>

namespace yasuzume::graph
{
  enum Direction {
    LeftToRight,
    RightToLeft,
    Undirected,
  };

  class GraphNode {
  public:
    GraphNode( std::string );
    GraphNode( const GraphNode& );
    GraphNode( GraphNode&& );
    GraphNode& operator=( const GraphNode& );
    GraphNode& operator=( GraphNode&& );
    ~GraphNode() noexcept;

    static void create_edge( GraphNode&, GraphNode&, float, Direction );

    class Node {
    public:
      Node( GraphNode& );
      Node( const Node& );
      Node( Node&& );
      Node& operator=( const Node& );
      Node& operator=( Node&& );
      ~Node() noexcept;

      [[nodiscard]] GraphNode& get() const;
    private:
      GraphNode& main;
    };

    class Edge : std::enable_shared_from_this<Edge>
    {
    public:
      Edge( std::shared_ptr<GraphNode::Node>, std::shared_ptr<GraphNode::Node>, const float&, const Direction& );
      Edge( const Edge& );
      Edge( Edge&& );
      Edge& operator=( const Edge& );
      Edge& operator=( Edge&& );
      ~Edge() noexcept;

      [[nodiscard]] bool operator<( const Edge& ) const;
      [[nodiscard]] bool operator>( const Edge& ) const;
      [[nodiscard]] bool operator==( const Edge& ) const;
      [[nodiscard]] bool operator<=( const Edge& ) const;
      [[nodiscard]] bool operator>=( const Edge& ) const;
      [[nodiscard]] bool operator!=( const Edge& ) const;

      [[nodiscard]] float get_weight() const;
      [[nodiscard]] Direction get_direction() const;
      void set_direction( Direction );
      void set_weight( float );
    private:
      float weight = 0;
      Direction direction;
      std::shared_ptr<GraphNode::Node> left_node;
      std::shared_ptr<GraphNode::Node> right_node;
    };

    void add_edge( std::shared_ptr<Edge> );
    void remove_edge( std::shared_ptr<Edge> );
  private:
    std::string name;
    std::shared_ptr<Node> node;
    std::set<std::shared_ptr<Edge>> edges{};
  };
}

#endif // !Y_GRAPH_NODES_HPP