#include "../Headers/Boruvka.hpp"

typedef std::shared_ptr<yasuzume::graph::GraphNode::Edge> EdgePtr;
typedef std::shared_ptr<yasuzume::graph::GraphNode>       NodePtr;
typedef std::vector<std::set<NodePtr>>::iterator          NodePtrSetIterator;

namespace yasuzume::graph::mst
{
  UndirectedGraph Boruvka::create_minimum_spanning_tree( const UndirectedGraph& _graph )
  {
    // Construct new graph by applying Boruvka algorithm and create a minimum spanning tree
    UndirectedGraph minimum_spanning_tree { UndirectedGraph::create_new_graph_from_nodes( _graph ) };

    // Initialize Graph as set of individual clusters
    std::vector<std::set<NodePtr>> clusters {};

    for( const auto& i : _graph.get_nodes() )
    {
      std::set temp { i };
      clusters.emplace_back( temp );
    }
    std::set<EdgePtr> edges {};
    while( std::ssize( clusters ) > 1 )
      for( auto it { 0 }; it < std::ssize( clusters ); it++ )
      {
        EdgePtr edge_to_add;
        auto    shortest_distance { INFINITY };
        auto    left_contains { false };

        // Find the shortest edge in a cluster
        for( auto cluster { clusters.at( it ) }; const auto& i : cluster )
          for( const auto& j : i->get_edges() )
            if( !edges.contains( j ) && j->get_weight() < shortest_distance )
            {
              // Check which node is in the cluster; if both, discard value
              const auto left_contains_temp = cluster.contains( j->get_left().lock() );
              if( ( left_contains_temp && cluster.contains( j->get_right().lock() ) ) ) continue;
              edge_to_add = j;
              left_contains = left_contains_temp;
              shortest_distance = j->get_weight();
            }
        // Find the other cluster
        NodePtrSetIterator                                                                            iterator_remove {
          std::ranges::find_if( clusters, [ &, left_contains, edge_to_add ]( const std::set<NodePtr>& _set )
          {
            return left_contains ? _set.contains( edge_to_add->get_right().lock() ) : _set.contains( edge_to_add->get_left().lock() );
          } )
        };

        // Merge clusters
        clusters.at( it ).merge( *iterator_remove );
        if( clusters.begin() + it > iterator_remove ) --it;
        clusters.erase( iterator_remove );

        // Add edge to the tree
        edges.emplace( edge_to_add );
      }

    for( const auto& edge : edges ) minimum_spanning_tree.add_edge( edge );

    return minimum_spanning_tree;
  }
}
