#include <DFS.hpp>
#include <stack>

namespace yasuzume::graph
{
  Path DFS::path_search( const NodePtr& _starting_node, const NodePtr& _goal_node )
  {
    Path path {};
    std::stack<std::pair<EdgePtr, float>> stack {};



    return path;
  }

  ConnectedTree DFS::connected_search( const NodePtr& _starting_node )
  {
    std::stack<NodePtr> stack {};
    stack.push( _starting_node );
    std::set visited_nodes { _starting_node };
    ConnectedTree connected_tree {};
    connected_tree.path.emplace_back( _starting_node );

    while( !stack.empty() )
    {
      const auto node { stack.top() };
      stack.pop();

      for( const auto& i : node->get_edges() )
      {
        if( !visited_nodes.contains( i->get_left().lock() ) )
        {
          stack.push( i->get_left().lock() );
          visited_nodes.emplace( i->get_left().lock() );
          connected_tree.path.emplace_back( i->get_left().lock() );
        }
        else if( !visited_nodes.contains( i->get_right().lock() ) )
        {
          stack.push( i->get_right().lock() );
          visited_nodes.emplace( i->get_right().lock() );
          connected_tree.path.emplace_back( i->get_right().lock() );
        }
      }
    }

    return connected_tree;
  }
}
