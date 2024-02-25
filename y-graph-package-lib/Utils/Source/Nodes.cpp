#include "../Headers/Nodes.hpp"

namespace yasuzume::graph
{

#pragma region Edge

#pragma region Constructors

  GraphNode::Edge::Edge( std::shared_ptr<GraphNode::Node> _left_node, std::shared_ptr<GraphNode::Node> _right_node, float _weight, Direction _direction )
    : left_node( _left_node ), right_node( _right_node ), weight( _weight ), direction( _direction ) {}

  GraphNode::Edge::Edge(const Edge& other) = default;
  
  GraphNode::Edge::Edge(const Edge&& other ) = default;

  GraphNode::Edge& GraphNode::Edge::operator=( const Edge& other ) = default;

  GraphNode::Edge& GraphNode::Edge::operator=( const Edge&& other ) = default;

  GraphNode::Edge::~Edge() = default;

#pragma endregion

#pragma region Operators

  bool GraphNode::Edge::operator<( const Edge& other ) const
  {
    return weight < other.get_weight();
  }

  bool GraphNode::Edge::operator<=( const Edge& other ) const
  {
    return weight < other.get_weight();
  }

  bool GraphNode::Edge::operator>( const Edge& other ) const
  {
    return weight > other.get_weight();
  }

  bool GraphNode::Edge::operator>=( const Edge& other ) const
  {
    return weight >= other.get_weight();
  }

  bool GraphNode::Edge::operator==( const Edge& other ) const
  {
    return weight == other.get_weight();
  }

  bool GraphNode::Edge::operator!=( const Edge& other ) const
  {
    return weight != other.get_weight();
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

  void GraphNode::Edge::set_direction( Direction _direction )
  {
    direction = _direction;
    switch( direction )
    {
    case LeftToRight:
      left_node->get().add_edge( std::make_shared<GraphNode::Edge>( this ) );
      right_node->get().remove_edge( std::make_shared<GraphNode::Edge>( this ) );
      break;
    case RightToLeft:
      right_node->get().add_edge( std::make_shared<GraphNode::Edge>( this ) );
      left_node->get().remove_edge( std::make_shared<GraphNode::Edge>( this ) );
      break;
    case Undirected:
    default:
      left_node->get().add_edge( std::make_shared<GraphNode::Edge>( this ) );
      right_node->get().add_edge( std::make_shared<GraphNode::Edge>( this ) );
      break;
    }
  }

  void GraphNode::Edge::set_weight( float _weight )
  {
    weight = _weight;
  }

#pragma endregion

#pragma endregion

#pragma region Node

  GraphNode::Node::Node( GraphNode& _main ) : main( _main ) {}

  GraphNode::Node::Node( const Node& other ) = default;

  GraphNode::Node::Node( const Node&& other ) = default;

  GraphNode::Node& GraphNode::Node::operator=( const GraphNode::Node& ) = default;

  GraphNode::Node& GraphNode::Node::operator=( const GraphNode::Node&& ) = default;

  GraphNode::Node::~Node() noexcept = default;

  GraphNode& GraphNode::Node::get() const
  {
    return main;
  }

#pragma endregion

#pragma region GraphNode

  void GraphNode::create_edge( GraphNode& left, GraphNode& right, const float& weight, const Direction& direction )
  {
    auto edge = std::make_shared<GraphNode::Edge>( left.node, right.node, weight, direction );
    switch( direction )
    {
    case LeftToRight:
      left.add_edge(edge);
      break;
    case RightToLeft:
      right.add_edge(edge);
      break;
    case Undirected:
    default:
      left.add_edge( edge );
      right.add_edge( edge );
      break;
    }
  }

  GraphNode::GraphNode( std::string _name ) : name( name ) 
  {
    node = std::make_shared<Node>( this );
  }

  GraphNode::GraphNode( const GraphNode& other ) = default;

  GraphNode::GraphNode( const GraphNode& other ) = default;
  GraphNode::GraphNode( const GraphNode&& other ) = default;
  GraphNode& GraphNode::operator=( const GraphNode& other ) = default;
  GraphNode& GraphNode::operator=( const GraphNode&& other ) = default;
  GraphNode::~GraphNode() noexcept = default;

  void GraphNode::add_edge( std::shared_ptr<Edge> edge )
  {
    edges.insert( edge );
  }

  void GraphNode::remove_edge( std::shared_ptr<Edge> edge )
  {
    edges.erase( edge );
  }

#pragma endregion 

}