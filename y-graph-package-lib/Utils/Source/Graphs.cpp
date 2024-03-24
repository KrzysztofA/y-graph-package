#include "../Headers/Graphs.hpp"

#include <algorithm>
#include <memory>
#include <sstream>

namespace yasuzume::graph
{
  Graph Graph::create_new_graph_from_nodes( const Graph& _old_graph )
  {
    Graph new_graph {};
    for( auto& node : _old_graph.nodes_vector ) new_graph.add_node( node->get_name() );
    return new_graph;
  }

  void Graph::add_node( const std::string& _name )
  {
    auto node { std::make_shared<GraphNode>( _name ) };
    if( !nodes_set.contains( _name ) )
    {
      if( std::ssize( _name ) > longest_node_name ) longest_node_name = std::ssize( _name );
      nodes_vector.emplace_back( node );
      nodes_set.emplace( _name, std::make_pair( nodes_vector.size() - 1, node ) );
      for( auto& i : graph_table_representation ) i.emplace_back( INFINITY );
      std::vector<float> temp( graph_table_representation.at( 0 ).size() );
      std::ranges::fill( temp, INFINITY );
      graph_table_representation.emplace_back( temp );
    }
  }

  void Graph::add_edge( const std::shared_ptr<GraphNode::Edge>& _edge )
  {
    edges.insert( _edge );
    const int left_index { nodes_set.at( _edge->get_left().lock()->get_name() ).first };
    const int right_index { nodes_set.at( _edge->get_right().lock()->get_name() ).first };
    if( graph_table_representation.at( left_index ).at( right_index ) > _edge->get_weight() )
    {
      graph_table_representation.at( left_index ).at( right_index ) = _edge->get_weight();
      graph_table_representation.at( right_index ).at( left_index ) = _edge->get_weight();
    }
  }

  std::string Graph::get_graph_table_stringified() const
  {
    std::stringstream sstream {};
    sstream.width( longest_node_name );
    sstream << " " << " ";
    for( const auto& i : get_nodes() )
    {
      sstream.width( longest_node_name );
      sstream << i->get_name() << " | ";
    }
    sstream << "\n";

    for( auto i { 0 }; i < std::ssize( graph_table_representation ) && i < std::ssize( get_nodes() ); i++ )
    {
      sstream.width( longest_node_name );
      sstream << get_nodes().at( i )->get_name() << " ";
      for( const auto& j : graph_table_representation.at( i ) )
      {
        sstream.width( longest_node_name );
        sstream << j << " | ";
      }
      sstream << "\n";
    }

    return sstream.str();
  }

  void Graph::manually_override_longest_node_name( const long long& _new_longest )
  {
    longest_node_name = _new_longest;
  }

  std::set<std::shared_ptr<GraphNode::Edge>> Graph::get_edges() const
  {
    return edges;
  }

  std::vector<std::shared_ptr<GraphNode>> Graph::get_nodes() const
  {
    std::vector<std::shared_ptr<GraphNode>> return_vector( nodes_vector.size() );
    std::ranges::copy( nodes_vector.begin(), nodes_vector.end(), return_vector.begin() );
    return return_vector;
  }

  std::shared_ptr<GraphNode> Graph::get_node( const std::string& _name ) const
  {
    return nodes_set.at( _name ).second;
  }

  std::vector<std::vector<float>> Graph::get_graph_table_representation() const
  {
    return graph_table_representation;
  }

  float Graph::get_total_graph_weight() const
  {
    auto sum { 0.0f };
    for( const auto& i : edges ) sum += i->get_weight();
    return sum;
  }

  UndirectedGraph::UndirectedGraph( const Graph& _graph )
  {
    for( const auto& node : _graph.get_nodes() ) add_node( node->get_name() );
  }

  void UndirectedGraph::add_connection( const int _index_left, const int _index_right, const float _weight )
  {
    edges.insert( GraphNode::create_edge( nodes_vector.at( _index_left ), nodes_vector.at( _index_right ), _weight, Undirected ) );
    if( graph_table_representation.at( _index_left ).at( _index_right ) > _weight )
    {
      graph_table_representation.at( _index_left ).at( _index_right ) = _weight;
      graph_table_representation.at( _index_right ).at( _index_left ) = _weight;
    }
  }

  void UndirectedGraph::add_connection( const std::string& _name_left, const std::string& _name_right, const float _weight )
  {
    edges.insert( GraphNode::create_edge( nodes_set.at( _name_left ).second, nodes_set.at( _name_right ).second, _weight, Undirected ) );
    const int left_index{ nodes_set.at( _name_left ).first };
    const int right_index{ nodes_set.at( _name_right ).first };
    if( graph_table_representation.at( left_index ).at( right_index ) > _weight )
    {
      graph_table_representation.at( left_index ).at( right_index ) = _weight;
      graph_table_representation.at( right_index ).at( left_index ) = _weight;
    }
  }
}
