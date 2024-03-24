#include <utility>

#include "../Headers/Nodes.hpp"

#include <cassert>
#include <sstream>

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

  bool GraphNode::Edge::is_valid_left() const
  {
    return direction == Undirected || direction == RightToLeft;
  }

  bool GraphNode::Edge::is_valid_right() const
  {
    return direction == Undirected || direction == LeftToRight;
  }

  std::string GraphNode::Edge::get_stringified() const
  {
    std::stringstream sstream{};
    switch( direction )
    {
    case Undirected:
      sstream << left_node.lock()->get_name() << " < = ";
      sstream.width( 5 );
      sstream << weight << " = > " << right_node.lock()->get_name();
      break;
    case LeftToRight:
      sstream << left_node.lock()->get_name() << " = = " << weight << " = > " << right_node.lock()->get_name();
      break;
    case RightToLeft:
      sstream << left_node.lock()->get_name() << " < = " << weight << " = = " << right_node.lock()->get_name();
      break;
    }
    return sstream.str();
  }

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

  std::weak_ptr<GraphNode> GraphNode::Edge::get_other( const std::shared_ptr<GraphNode>& _node ) const
  {
    assert( ( left_node.lock() == _node || right_node.lock() == _node) );
    return _node == left_node.lock() ? right_node : left_node;
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

  std::string GraphNode::EdgeSummed::get_stringified() const
  {
    std::stringstream sstream{};
    sstream << "{" << edge->get_stringified();
    sstream << " = " << cumulated_weight << " }";
    return sstream.str();
  }

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

  std::vector<std::shared_ptr<GraphNode::EdgeSummed>> GraphNode::get_summed_edges( const float& _sum ) const
  {
    std::vector<std::shared_ptr<EdgeSummed>> summed;
    summed.reserve( edges.size() );
    for( const auto& edge : edges )
    {
      auto temp { std::make_shared<EdgeSummed>( edge, edge->get_weight() + _sum ) };
      summed.emplace_back( temp );
    }
    return summed;
  }

  std::string GraphNode::get_name()
  {
    return name;
  }

#pragma endregion
}
