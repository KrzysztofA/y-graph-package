#ifndef Y_GRAPH_NODES_HPP
#define Y_GRAPH_NODES_HPP

#include <memory>
#include <Numeric.inl>
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

      [[nodiscard]] std::string              get_stringified() const;
      [[nodiscard]] float                    get_weight() const;
      [[nodiscard]] Direction                get_direction() const;
      [[nodiscard]] std::weak_ptr<GraphNode> get_left() const;
      [[nodiscard]] std::weak_ptr<GraphNode> get_right() const;
      [[nodiscard]] std::weak_ptr<GraphNode> get_other( const std::shared_ptr<GraphNode>& ) const;
      void                                   set_direction( Direction );
      void                                   set_weight( float );
      [[nodiscard]] bool                     is_valid_left() const;
      [[nodiscard]] bool                     is_valid_right() const;

    private:
      float                 weight = 0;
      Direction             direction;
      std::weak_ptr<GraphNode> left_node;
      std::weak_ptr<GraphNode> right_node;
    };

    struct EdgeSummed
    {
      EdgeSummed( std::shared_ptr<Edge> _edge, const float& _cumulated_weight ) : edge( std::move( _edge ) ), cumulated_weight( _cumulated_weight ) {}
      EdgeSummed() = default;
      EdgeSummed( const EdgeSummed& ) = default;
      EdgeSummed( EdgeSummed&& ) noexcept = default;
      EdgeSummed& operator=( const EdgeSummed& ) = default;
      EdgeSummed& operator=( EdgeSummed&& ) noexcept = default;
      ~EdgeSummed() noexcept = default;

      [[nodiscard]] bool operator<( const EdgeSummed& _rhs ) const { return cumulated_weight < _rhs.cumulated_weight; }
      [[nodiscard]] bool operator>( const EdgeSummed& _rhs ) const { return cumulated_weight > _rhs.cumulated_weight; }
      [[nodiscard]] bool operator==( const EdgeSummed& _rhs ) const { return edge == _rhs.edge; }
      [[nodiscard]] bool operator<=( const EdgeSummed& _rhs ) const { return cumulated_weight <= _rhs.cumulated_weight; }
      [[nodiscard]] bool operator>=( const EdgeSummed& _rhs ) const { return cumulated_weight >= _rhs.cumulated_weight; }
      [[nodiscard]] bool operator!=( const EdgeSummed& _rhs ) const { return this != &_rhs; }

      [[nodiscard]] std::string get_stringified() const;

      std::shared_ptr<Edge> edge = nullptr;
      float cumulated_weight = 0;
    };

    static std::shared_ptr<Edge> create_edge( const std::shared_ptr<GraphNode>&, const std::shared_ptr<GraphNode>&, float, Direction );
    void                         add_edge( const std::shared_ptr<Edge>& );
    void                         remove_edge( const std::shared_ptr<Edge>& );

    std::set<std::shared_ptr<Edge>>                     get_edges();
    std::vector<std::shared_ptr<GraphNode::EdgeSummed>> get_summed_edges( const float& ) const;
    std::string                                         get_name();

  private:
    std::string                     name;
    std::set<std::shared_ptr<Edge>> edges {};
  };
}

#endif // !Y_GRAPH_NODES_HPP
