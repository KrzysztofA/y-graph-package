#ifndef Y_GRAPH_MST_MINIMUM_SPANNING_TREE_ALGORITHM_INL
#define Y_GRAPH_MST_MINIMUM_SPANNING_TREE_ALGORITHM_INL

#include "../../Utils/Headers/Graphs.hpp"

namespace yasuzume::graph::mst
{
  class MinimumSpanningTreeAlgorithm
  {
  public:
    MinimumSpanningTreeAlgorithm();
    MinimumSpanningTreeAlgorithm( const MinimumSpanningTreeAlgorithm& ) = default;
    MinimumSpanningTreeAlgorithm( MinimumSpanningTreeAlgorithm&& ) noexcept = default;
    MinimumSpanningTreeAlgorithm& operator=( const MinimumSpanningTreeAlgorithm& ) = default;
    MinimumSpanningTreeAlgorithm& operator=( MinimumSpanningTreeAlgorithm&& ) noexcept = default;
    virtual ~MinimumSpanningTreeAlgorithm() noexcept = default;

    virtual Graph create_minimum_spanning_tree( const Graph& ) = 0;
  };
}

#endif // !Y_GRAPH_MST_MINIMUM_SPANNING_TREE_ALGORITHM_INL