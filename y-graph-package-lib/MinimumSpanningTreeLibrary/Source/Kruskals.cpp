#include "../Headers/Kruskals.hpp"

#include "../../SortsLibrary/Sorts.inl"

typedef std::shared_ptr<yasuzume::graph::GraphNode::Edge> EdgePtr;
typedef std::shared_ptr<yasuzume::graph::GraphNode> NodePtr;

namespace yasuzume::graph::mst
{
  Graph Kruskals::create_minimum_spanning_tree( const Graph& _graph )
  {
    // Get edges from the graph
    std::vector<EdgePtr> edges( _graph.get_edges().size() );

    // Sort, remove loops and duplicate edges

    // Sort by names
    auto                 get_sorted_joined_name {
      []( const EdgePtr& _edge )
      {
        const auto name_left { _edge->get_left()->get().lock()->get_name() };
        const auto name_right { _edge->get_right()->get().lock()->get_name() };
        return name_left > name_right ? name_left + name_right : name_right + name_left;
      }
    };

    std::ranges::sort( edges.begin(), edges.end(), [get_sorted_joined_name]( const EdgePtr& _a, const EdgePtr& _b )
    {
      const auto name_a { get_sorted_joined_name( _a ) };
      const auto name_b { get_sorted_joined_name( _b ) };
      return name_a > name_b;
    } );

    // Remove duplicates and loops
    for( auto i { 0 }; i < std::ssize( edges ); i++ )
      for( auto j { i + 1 }; j < std::ssize( edges ); j++ )
        if( get_sorted_joined_name( edges.at( i ) ) == get_sorted_joined_name( edges.at( j ) ) )
        {
          if( edges.at( i )->get_weight() >= edges.at( j )->get_weight() )
          {
            edges.erase( std::begin( edges ) + j );
            j--;
          }
          else
          {
            edges.erase( std::begin( edges ) + i );
            j = i;
          }
        }

    // Sort by weights
    std::ranges::sort( edges.begin(), edges.end(), []( const EdgePtr& _a, const EdgePtr& _b )
    {
      return _a->get_weight() > _b->get_weight();
    } );

    // Construct new graph by applying Kruskal algorithm and create a minimum spanning tree
    auto minimum_spanning_tree = Graph::create_new_graph_from_nodes( _graph );

    // Populate new graph by applying Kruskals algorithm

    // Select the shortest edge, check if edge doesn't cause cycle, if not add it to the graph

    std::vector<std::set<NodePtr>> explored_connections {};
    for( const auto& i : edges )
    {
      int set_with_left { -1 };
      int set_with_right { -1 };

      // If is in the same set, skip, if belongs to 2 different sets, merge, otherwise if one exists in a set, add another to the set, else add both to a new set
      for( auto index { 0 }; index < std::ssize( explored_connections ); index++ )
      {
        if( explored_connections.at( index ).contains( i->get_left()->get().lock() ) ) set_with_left = index;
        if( explored_connections.at( index ).contains( i->get_right()->get().lock() ) ) set_with_right = index;
        if( set_with_left != -1 && set_with_right != -1 ) break;
      }

      if( set_with_left != -1 && set_with_right != -1 && set_with_left == set_with_right ) continue;
      if( set_with_left != -1 && set_with_right != -1 )
      {
        explored_connections.at( set_with_left ).merge( explored_connections.at( set_with_right ) );
        explored_connections.erase( explored_connections.begin() + set_with_right );
      }
      else if( set_with_left != -1 ) explored_connections.at( set_with_left ).emplace( i->get_right()->get().lock() );
      else if( set_with_right != -1 ) explored_connections.at( set_with_right ).emplace( i->get_left()->get().lock() );
      minimum_spanning_tree.add_edge( i );
    }

    return minimum_spanning_tree;
  }
}
