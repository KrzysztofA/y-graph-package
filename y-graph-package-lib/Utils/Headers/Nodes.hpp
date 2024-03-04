#ifndef Y_GRAPH_NODES_HPP
#define Y_GRAPH_NODES_HPP

#include <memory>
#include <set>
#include <string>

namespace yasuzume::graph
{
  enum Direction
  {
    LeftToRight,
    RightToLeft,
    Undirected,
  };

  class GraphNode : std::enable_shared_from_this<GraphNode>
  {
  public:
    explicit GraphNode( std::string );
    GraphNode( const GraphNode& );
    GraphNode( GraphNode&& ) noexcept;
    GraphNode& operator=( const GraphNode& );
    GraphNode& operator=( GraphNode&& ) noexcept;
    ~GraphNode() noexcept;

    class Edge : std::enable_shared_from_this<Edge>
    {
    public:
      Edge( std::weak_ptr<GraphNode>, std::weak_ptr<GraphNode>, const float&, const Direction& );
      Edge( const Edge& );
      Edge( Edge&& ) noexcept;
      Edge& operator=( const Edge& );
      Edge& operator=( Edge&& ) noexcept;
      ~Edge() noexcept;

      [[nodiscard]] bool operator<( const Edge& ) const;
      [[nodiscard]] bool operator>( const Edge& ) const;
      [[nodiscard]] bool operator==( const Edge& ) const;
      [[nodiscard]] bool operator<=( const Edge& ) const;
      [[nodiscard]] bool operator>=( const Edge& ) const;
      [[nodiscard]] bool operator!=( const Edge& ) const;

      [[nodiscard]] float                 get_weight() const;
      [[nodiscard]] Direction             get_direction() const;
      [[nodiscard]] std::weak_ptr<GraphNode> get_left() const;
      [[nodiscard]] std::weak_ptr<GraphNode> get_right() const;
      void                                set_direction( Direction );
      void                                set_weight( float );

    private:
      float                 weight = 0;
      Direction             direction;
      std::weak_ptr<GraphNode> left_node;
      std::weak_ptr<GraphNode> right_node;
    };

    static std::shared_ptr<Edge> create_edge( const std::shared_ptr<GraphNode>&, const std::shared_ptr<GraphNode>&, float, Direction );
    void                         add_edge( const std::shared_ptr<Edge>& );
    void                         remove_edge( const std::shared_ptr<Edge>& );

    std::set<std::shared_ptr<Edge>> get_edges();
    std::string                     get_name();

  private:
    std::string                     name;
    std::set<std::shared_ptr<Edge>> edges {};
  };
}

#endif // !Y_GRAPH_NODES_HPP
