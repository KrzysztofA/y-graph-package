#include "../Headers/ReverseDelete.hpp"

#include <algorithm>

typedef std::shared_ptr<yasuzume::graph::GraphNode::Edge> EdgePtr;
typedef std::shared_ptr<yasuzume::graph::GraphNode>       NodePtr;

namespace yasuzume::graph::mst
{
  UndirectedGraph ReverseDelete::create_minimum_spanning_tree( const UndirectedGraph& _graph )
  {
    std::unordered_map<NodePtr, int> node_reference_count {};
    for( const auto& i : _graph.get_nodes() ) node_reference_count.emplace( i, 0 );
    for( const auto& i : _graph.get_edges() )
    {
      ++node_reference_count.at( i->get_left().lock() );
      ++node_reference_count.at( i->get_right().lock() );
    }

    std::vector<EdgePtr> edges {};
    for( auto& i : _graph.get_edges() ) edges.emplace_back( i );
    std::ranges::sort( edges, []( const EdgePtr& _i, const EdgePtr& _j ) { return _i->get_weight() > _j->get_weight(); } );


    for( auto i { edges.begin() }; i != edges.end(); )
    {
      auto                 valid { false };
      std::vector<EdgePtr> edges_cpy( edges.size() );
      std::ranges::copy( edges.begin(), edges.end(), edges_cpy.begin() );
      edges_cpy.erase( std::ranges::find( edges_cpy.begin(), edges_cpy.end(), *i ) );
      std::unordered_map<NodePtr, int> reference_count {};
      for( const auto& z : _graph.get_nodes() ) reference_count.emplace( z, 0 );
      auto              o { edges_cpy.begin() };
      std::set<NodePtr> travelled_nodes {};
      while( o != edges_cpy.end() )
      {
        reference_count.at( ( *o )->get_left().lock() )++;
        reference_count.at( ( *o )->get_right().lock() )++;
        travelled_nodes.insert( ( *o )->get_left().lock() );
        travelled_nodes.insert( ( *o )->get_right().lock() );
        edges_cpy.erase( o );
        o = std::ranges::find_if( edges_cpy.begin(), edges_cpy.end(), [travelled_nodes]( const EdgePtr& _ptr ) { return travelled_nodes.contains( _ptr->get_left().lock() ) || travelled_nodes.contains( _ptr->get_right().lock() ); } );
      }
      if( std::ranges::any_of( reference_count, []( const std::pair<NodePtr, int>& _pair ) { return _pair.second == 0; } ) ) valid = false;
      else valid = true;

      if( valid ) i = edges.erase( i );
      else ++i;
    }
    UndirectedGraph minimum_spanning_tree { Graph::create_new_graph_from_nodes( _graph ) };
    for( const auto& edge : edges ) minimum_spanning_tree.add_edge( edge );
    return minimum_spanning_tree;
  }
}
