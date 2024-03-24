#include <Dijkstra.hpp>
#include <print>
#include <ValidValue.inl>

typedef std::shared_ptr<yasuzume::graph::GraphNode::EdgeSummed> EdgeSum;

namespace yasuzume::graph::shortest_path
{
  ShortestPathTree Dijkstra::create_shortest_path( const NodePtr& _starting_node, const UndirectedGraph& _graph )
  {
    // Initialize Graph
    ShortestPathTree  shortest_path { initialize_shortest_path_tree( _starting_node, _graph.get_nodes() ) };
    std::set<NodePtr> visited_nodes {};

    std::set<EdgeSum, bool( * )( const EdgeSum&, const EdgeSum& )> viable_edges( []( const EdgeSum& _first, const EdgeSum& _second )
    {
      return !utils::compare_almost( _first->cumulated_weight, _second->cumulated_weight )
               ? _first->cumulated_weight < _second->cumulated_weight
               : _first->edge->get_left().lock()->get_name() + _first->edge->get_right().lock()->get_name() < _second->edge->get_left().lock()->get_name() + _second->edge->get_right().lock()->get_name();
    } );
    viable_edges.insert_range( _starting_node->get_summed_edges( 0 ) );
    std::set<EdgeSum> used_edges {};
    visited_nodes.emplace( _starting_node );

    while( visited_nodes.size() < _graph.get_nodes().size() )
      for( auto j { viable_edges.begin() }; j != viable_edges.end(); )
      {
        auto i { *j };
        utils::ValidValue left_node { i->edge->get_left().lock() };
        utils::ValidValue right_node { i->edge->get_right().lock() };
        left_node.second = !visited_nodes.contains( left_node.first );
        right_node.second = !visited_nodes.contains( right_node.first );
        if( left_node.second )
        {
          used_edges.emplace( i );
          visited_nodes.emplace( left_node.first );
          viable_edges.insert_range( left_node.first->get_summed_edges( i->cumulated_weight ) );
          shortest_path.tree.at( left_node.first ).set_predecessor_weight( right_node.first, i->cumulated_weight );
          j = viable_edges.begin();
        }
        else if( right_node.second )
        {
          used_edges.emplace( i );
          visited_nodes.emplace( right_node.first );
          viable_edges.insert_range( right_node.first->get_summed_edges( i->cumulated_weight ) );
          shortest_path.tree.at( right_node.first ).set_predecessor_weight( left_node.first, i->cumulated_weight );
          j = viable_edges.begin();
        }
        else ++j;
      }

    for( const auto& i : used_edges ) shortest_path.path.emplace_back( i->edge );

    return shortest_path;
  }

  ShortestPathTree Dijkstra::create_shortest_path( const NodePtr& _starting_node, const DirectedGraph& _graph )
  {
    // Initialize Graph
    ShortestPathTree  shortest_path { initialize_shortest_path_tree( _starting_node, _graph.get_nodes() ) };
    std::set<NodePtr> visited_nodes {};

    std::set<EdgeSum, bool( * )( const EdgeSum&, const EdgeSum& )> viable_edges( []( const EdgeSum& _first, const EdgeSum& _second )
    {
      return !utils::compare_almost( _first->cumulated_weight, _second->cumulated_weight )
               ? _first->cumulated_weight < _second->cumulated_weight
               : _first->edge->get_left().lock()->get_name() + _first->edge->get_right().lock()->get_name() < _second->edge->get_left().lock()->get_name() + _second->edge->get_right().lock()->get_name();
    } );
    viable_edges.insert_range( _starting_node->get_summed_edges( 0 ) );
    std::set<EdgeSum> used_edges {};
    visited_nodes.emplace( _starting_node );

    while( visited_nodes.size() < _graph.get_nodes().size() )
      for( auto j { viable_edges.begin() }; j != viable_edges.end(); )
      {
        auto i { *j };
        utils::ValidValue left_node { i->edge->get_left().lock() };
        utils::ValidValue right_node { i->edge->get_right().lock() };
        left_node.second = !visited_nodes.contains( left_node.first ) && i->edge->is_valid_left();
        right_node.second = !visited_nodes.contains( right_node.first ) && i->edge->is_valid_right();
        if( left_node.second )
        {
          used_edges.emplace( i );
          visited_nodes.emplace( left_node.first );
          viable_edges.insert_range( left_node.first->get_summed_edges( i->cumulated_weight ) );
          shortest_path.tree.at( left_node.first ).set_predecessor_weight( right_node.first, i->cumulated_weight );
          j = viable_edges.begin();
        }
        else if( right_node.second )
        {
          used_edges.emplace( i );
          visited_nodes.emplace( right_node.first );
          viable_edges.insert_range( right_node.first->get_summed_edges( i->cumulated_weight ) );
          shortest_path.tree.at( right_node.first ).set_predecessor_weight( left_node.first, i->cumulated_weight );
          j = viable_edges.begin();
        }
        else ++j;
      }

    for( const auto& i : used_edges ) shortest_path.path.emplace_back( i->edge );

    return shortest_path;
  }
}
