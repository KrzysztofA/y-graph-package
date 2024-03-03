#include "../Headers/Graphs.hpp"

#include <algorithm>
#include <memory>

namespace yasuzume::graph
{
  Graph Graph::create_new_graph_from_nodes( const Graph& _old_graph )
  {
    Graph new_graph{};
    for( auto& node : _old_graph.nodes_vector ) new_graph.add_node( node->get_name() );
    return new_graph;
  }

  void yasuzume::graph::Graph::add_node( const std::string& _name )
  {
    auto node{ std::make_shared< GraphNode >( _name ) };
    if( !nodes_set.contains( _name ) )
    {
      nodes_vector.emplace_back( node );
      nodes_set.emplace( _name, std::make_pair( nodes_vector.size() - 1, node ) );
    }
  }

  void Graph::add_edge( const std::shared_ptr< GraphNode::Edge >& _edge )
  {
    edges.insert( _edge );
    graph_table_representation.at( nodes_set.at( _edge->get_left()->get().lock()->get_name() ).first ).at( nodes_set.at( _edge->get_right()->get().lock()->get_name() ).first ) = _edge->get_weight();
    graph_table_representation.at( nodes_set.at( _edge->get_right()->get().lock()->get_name() ).first ).at( nodes_set.at( _edge->get_left()->get().lock()->get_name() ).first ) = _edge->get_weight();
  }

  std::set< std::shared_ptr< GraphNode::Edge > > Graph::get_edges() const
  {
    return edges;
  }

  void UndirectedGraph::add_connection( const int _index_left, const int _index_right, const float _weight )
  {
    edges.insert( GraphNode::create_edge( nodes_vector.at( _index_left ), nodes_vector.at( _index_right ), _weight, Undirected ) );
    graph_table_representation.at( _index_left ).at( _index_right ) = _weight;
    graph_table_representation.at( _index_right ).at( _index_left ) = _weight;
  }

  void UndirectedGraph::add_connection( const std::string& _name_left, const std::string& _name_right, const float _weight )
  {
    edges.insert( GraphNode::create_edge( nodes_set.at( _name_left ).second, nodes_set.at( _name_right ).second, _weight, Undirected ) );
    graph_table_representation.at( nodes_set.at( _name_left ).first ).at( nodes_set.at( _name_right ).first ) = _weight;
    graph_table_representation.at( nodes_set.at( _name_right ).first ).at( nodes_set.at( _name_left ).first ) = _weight;
  }
}
