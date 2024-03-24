#include <BellmanFord.hpp>
#include <ranges>

namespace yasuzume::graph::shortest_path
{
  ShortestPathTree BellmanFord::create_shortest_path( const NodePtr& _starting_node, const UndirectedGraph& _graph )
  {
    // Initialize Graph
    ShortestPathTree  shortest_path { initialize_shortest_path_tree( _starting_node, _graph.get_nodes() ) };

    std::vector explored_nodes { _starting_node };
    explored_nodes.reserve( _graph.get_nodes().size() );

    // Explore all the edges
    for( auto i { 0 }; i < std::ssize( explored_nodes ); i++ )
    {
      for( auto node { explored_nodes.at( i ) }; const auto& edge : node->get_edges() )
        if( shortest_path.tree.at( edge->get_other( node ).lock() ).cumulated_weight > edge->get_weight() + shortest_path.tree.at( node ).cumulated_weight )
        {
          if( shortest_path.tree.at( edge->get_other( node ).lock() ).predecessor == nullptr ) explored_nodes.emplace_back( edge->get_other( node ).lock() );
          shortest_path.tree.at( edge->get_other( node ).lock() ).set_predecessor_weight_leading( node, edge->get_weight() + shortest_path.tree.at( node ).cumulated_weight, edge );
        }
    }

    for( const auto& edge : _graph.get_edges() )
    {
      const auto is_less_left { shortest_path.tree.at( edge->get_left().lock() ).cumulated_weight + edge->get_weight() < shortest_path.tree.at( edge->get_right().lock() ).cumulated_weight };
      const auto is_less_right { shortest_path.tree.at( edge->get_right().lock() ).cumulated_weight + edge->get_weight() < shortest_path.tree.at( edge->get_left().lock() ).cumulated_weight };
      if( edge->get_direction() == Undirected && ( is_less_left || is_less_right ) || edge->get_direction() == LeftToRight && is_less_right || edge->get_direction() == RightToLeft && is_less_left )
      {
        throw std::runtime_error( "Negative cycle exists" );
      }
    }

    for( const auto& val : shortest_path.tree | std::views::values ) if( val.leading_edge ) shortest_path.path.emplace_back( val.leading_edge );

    return shortest_path;
  }

  ShortestPathTree BellmanFord::create_shortest_path( const NodePtr& _starting_node, const DirectedGraph& _graph )
  {
    // Initialize Graph
    ShortestPathTree  shortest_path { initialize_shortest_path_tree( _starting_node, _graph.get_nodes() ) };

    std::vector explored_nodes { _starting_node };

    // Explore all the edges
    for( auto it { explored_nodes.begin() }; it != explored_nodes.end(); ++it )
    {
      for( const auto& edge : ( *it )->get_edges() )
        if( shortest_path.tree.at( edge->get_other( *it ).lock() ).cumulated_weight < edge->get_weight() + shortest_path.tree.at( *it ).cumulated_weight )
        {
          shortest_path.tree.at( edge->get_other( *it ).lock() ).set_predecessor_weight( *it, edge->get_weight() + shortest_path.tree.at( *it ).cumulated_weight );
          explored_nodes.push_back( edge->get_other( *it ).lock() );
        }
    }

    for( const auto& edge : _graph.get_edges() )
    {
      const auto is_less_left { shortest_path.tree.at( edge->get_left().lock() ).cumulated_weight + edge->get_weight() < shortest_path.tree.at( edge->get_right().lock() ).cumulated_weight };
      const auto is_less_right { shortest_path.tree.at( edge->get_right().lock() ).cumulated_weight + edge->get_weight() < shortest_path.tree.at( edge->get_left().lock() ).cumulated_weight };
      if( edge->get_direction() == Undirected && ( is_less_left || is_less_right ) || edge->get_direction() == LeftToRight && is_less_right || edge->get_direction() == RightToLeft && is_less_left )
      {
        throw std::runtime_error( "Negative cycle exists" );
      }
    }

    return shortest_path;
  }

}
