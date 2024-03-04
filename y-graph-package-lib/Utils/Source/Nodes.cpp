#include <utility>

#include "../Headers/Nodes.hpp"
#include "../Headers/Numeric.inl"

namespace yasuzume::graph
{
#pragma region Edge

#pragma region Constructors

  GraphNode::Edge::Edge( std::weak_ptr<GraphNode> _left_node, std::weak_ptr<GraphNode> _right_node, const float& _weight,
                         const Direction&      _direction )
    : weight( _weight ), direction( _direction ), left_node( std::move( _left_node ) ), right_node(
        std::move( _right_node ) ) {}

  GraphNode::Edge::Edge( const Edge& _other ) = default;
  GraphNode::Edge::Edge( Edge&& _other ) noexcept = default;
  GraphNode::Edge& GraphNode::Edge::operator=( const Edge& _other ) = default;
  GraphNode::Edge& GraphNode::Edge::operator=( Edge&& _other ) noexcept = default;
  GraphNode::Edge::~Edge() noexcept = default;

#pragma endregion

#pragma region Operators

  bool GraphNode::Edge::operator<( const Edge& _other ) const
  {
    return weight < _other.get_weight();
  }

  bool GraphNode::Edge::operator<=( const Edge& _other ) const
  {
    return weight < _other.get_weight();
  }

  bool GraphNode::Edge::operator>( const Edge& _other ) const
  {
    return weight > _other.get_weight();
  }

  bool GraphNode::Edge::operator>=( const Edge& _other ) const
  {
    return weight >= _other.get_weight();
  }

  bool GraphNode::Edge::operator==( const Edge& _other ) const
  {
    return utils::compare_almost( weight, _other.get_weight() );
  }

  bool GraphNode::Edge::operator!=( const Edge& _other ) const
  {
    return !utils::compare_almost( weight, _other.get_weight() );
  }

#pragma endregion

#pragma region Methods

  float GraphNode::Edge::get_weight() const
  {
    return weight;
  }

  Direction GraphNode::Edge::get_direction() const
  {
    return direction;
  }

  std::weak_ptr<GraphNode> GraphNode::Edge::get_left() const
  {
    return left_node;
  }

  std::weak_ptr<GraphNode> GraphNode::Edge::get_right() const
  {
    return right_node;
  }

  void GraphNode::Edge::set_direction( const Direction _direction )
  {
    direction = _direction;
    switch( direction )
    {
    case LeftToRight:
      {
        left_node.lock()->add_edge( shared_from_this() );
        right_node.lock()->remove_edge( shared_from_this() );
        break;
      }
    case RightToLeft:
      {
        right_node.lock()->add_edge( shared_from_this() );
        left_node.lock()->remove_edge( shared_from_this() );
        break;
      }
    case Undirected:
      {
        left_node.lock()->add_edge( shared_from_this() );
        right_node.lock()->add_edge( shared_from_this() );
        break;
      }
    }
  }

  void GraphNode::Edge::set_weight( const float _weight )
  {
    weight = _weight;
  }

#pragma endregion

#pragma endregion

#pragma region GraphNode

  std::shared_ptr<GraphNode::Edge> GraphNode::create_edge( const std::shared_ptr<GraphNode>& _left, const std::shared_ptr<GraphNode>& _right, float _weight, Direction _direction )
  {
    const auto edge = std::make_shared<Edge>( _left, _right, _weight, _direction );
    switch( _direction )
    {
    case LeftToRight:
      {
        _left->add_edge( edge );
        break;
      }
    case RightToLeft:
      {
        _right->add_edge( edge );
        break;
      }
    case Undirected:
      {
        _left->add_edge( edge );
        _right->add_edge( edge );
        break;
      }
    }

    return edge;
  }

  GraphNode::GraphNode( std::string _name ) : name( std::move( _name ) ) {}

  GraphNode::GraphNode( const GraphNode& _other ) = default;
  GraphNode::GraphNode( GraphNode&& _other ) noexcept = default;
  GraphNode& GraphNode::operator=( const GraphNode& _other ) = default;
  GraphNode& GraphNode::operator=( GraphNode&& _other ) noexcept = default;
  GraphNode::~GraphNode() noexcept = default;

  void GraphNode::add_edge( const std::shared_ptr<Edge>& _edge )
  {
    edges.insert( _edge );
  }

  void GraphNode::remove_edge( const std::shared_ptr<Edge>& _edge )
  {
    edges.erase( _edge );
  }

  std::set<std::shared_ptr<GraphNode::Edge>> GraphNode::get_edges()
  {
    return edges;
  }

  std::string GraphNode::get_name()
  {
    return name;
  }

#pragma endregion
}
