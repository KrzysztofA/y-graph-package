#include "../Headers/Kruskals.hpp"

#include <algorithm>
#include <iterator>

typedef std::shared_ptr<yasuzume::graph::GraphNode::Edge> EdgePtr;
typedef std::shared_ptr<yasuzume::graph::GraphNode> NodePtr;

namespace yasuzume::graph::mst
{
  UndirectedGraph Kruskals::create_minimum_spanning_tree( const UndirectedGraph& _graph )
  {
    // Get edges from the graph
    std::vector<EdgePtr> edges {};
    for( auto& i : _graph.get_edges() ) edges.emplace_back( i );

    // Sort by weights
    std::ranges::sort( edges.begin(), edges.end(), []( const EdgePtr& _a, const EdgePtr& _b )
    {
      return _a->get_weight() < _b->get_weight();
    } );

    // Construct new graph by applying Kruskal algorithm and create a minimum spanning tree
    UndirectedGraph minimum_spanning_tree { Graph::create_new_graph_from_nodes( _graph ) };

    // Populate new graph by applying Kruskals algorithm

    // Select the shortest edge, check if edge doesn't cause cycle, if not add it to the graph

    std::vector<std::set<NodePtr>> explored_connections {};
    for( const auto& i : edges )
    {
      if( i->get_left().lock() == i->get_right().lock() ) continue;
      int set_with_left { -1 };
      int set_with_right { -1 };

      // If is in the same set, skip, if belongs to 2 different sets, merge, otherwise if one exists in a set, add another to the set, else add both to a new set
      for( auto index { 0 }; index < std::ssize( explored_connections ); index++ )
      {
        //! This step could be parallelized
        if( explored_connections.at( index ).contains( i->get_left().lock() ) ) set_with_left = index;
        if( explored_connections.at( index ).contains( i->get_right().lock() ) ) set_with_right = index;
        if( set_with_left != -1 && set_with_right != -1 ) break;
      }

      if( set_with_left != -1 && set_with_right != -1 && set_with_left == set_with_right ) continue;
      else if( set_with_left != -1 && set_with_right != -1 )
      {
        explored_connections.at( set_with_left ).merge( explored_connections.at( set_with_right ) );
        explored_connections.erase( explored_connections.begin() + set_with_right );
      }
      else if( set_with_left != -1 ) explored_connections.at( set_with_left ).emplace( i->get_right().lock() );
      else if( set_with_right != -1 ) explored_connections.at( set_with_right ).emplace( i->get_left().lock() );
      else
      {
        std::set temp { i->get_left().lock(), i->get_right().lock() };
        explored_connections.emplace_back( temp );
      }
      minimum_spanning_tree.add_edge( i );
    }

    return minimum_spanning_tree;
  }
}
