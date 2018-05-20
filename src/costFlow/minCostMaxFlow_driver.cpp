/*PGR-GNU*****************************************************************
File: minCostMaxFlow_driver.cpp

Generated with Template by:
Copyright (c) 2015 pgRouting developers
Mail: project@pgrouting.org

Function's developer: 
Copyright (c) 2018 Maoguang Wang
Mail: xjtumg1007@gmail.com

------

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

********************************************************************PGR-GNU*/

#include "drivers/costFlow/minCostMaxFlow_driver.h"

#include <sstream>
#include <deque>
#include <vector>
#include <set>

#include "costFlow/pgr_minCostMaxFlow.hpp"

#include "cpp_common/pgr_alloc.hpp"
#include "cpp_common/pgr_assert.h"

// not needed
/*
template < class G >
static
std::vector<pgr_flow_t>
pgr_minCostMaxFlow(
        G &graph,
        std::vector<int64_t> sources,
        std::vector<int64_t> targets,
        bool only_cost) {
    std::sort(sources.begin(), sources.end());
    sources.erase(
            std::unique(sources.begin(), sources.end()),
            sources.end());

    std::sort(targets.begin(), targets.end());
    targets.erase(
            std::unique(targets.begin(), targets.end()),
            targets.end());

    Pgr_costFlow< G > fn_costFlow;
    return fn_costFlow.minCostMaxFlow(graph, sources, targets, only_cost);
}
*/


void
do_pgr_minCostMaxFlow(
        pgr_costFlow_t  *data_edges, size_t total_edges,
        int64_t *source_vertices, size_t size_source_verticesArr,
        int64_t *sink_vertices, size_t size_sink_verticesArr,
        bool only_cost,

        pgr_flow_t **return_tuples, size_t *return_count,
        char ** log_msg,
        char ** notice_msg,
        char ** err_msg) {
    std::ostringstream log;
    std::ostringstream err;
    std::ostringstream notice;
    try {
        pgassert(!(*log_msg));
        pgassert(!(*notice_msg));
        pgassert(!(*err_msg));
        pgassert(!(*return_tuples));
        pgassert(*return_count == 0);
        pgassert(total_edges != 0);

        std::vector<pgr_costFlow_t> edges(data_edges, data_edges + total_edges);
        std::set<int64_t> sources(
                source_vertices, source_vertices + size_source_verticesArr);
        std::set<int64_t> targets(
                sink_vertices, sink_vertices + size_sink_verticesArr);

        std::set<int64_t> vertices(sources);
        vertices.insert(targets.begin(), targets.end());

        if (vertices.size()
                != (sources.size() + targets.size())) {
            *err_msg = pgr_msg("A source found as sink");
            return;
        }

        pgrouting::graph::PgrCostFlowGraph digraph(
                edges, sources, targets);

        double min_cost; 
        min_cost = digraph.minCostMaxFlow();

        std::vector<pgr_flow_t> flow_edges;

        if (only_cost) {
            pgr_flow_t edge;
            edge.edge = -1;
            edge.source = -1;
            edge.target = -1;
            edge.flow = -1;
            edge.residual_capacity = -1;
            edge.cost = min_cost;
            edge.agg_cost = min_cost;
            flow_edges.push_back(edge);
        } else {
            flow_edges = digraph.get_flow_edges();
        }

        (*return_tuples) = pgr_alloc(flow_edges.size(), (*return_tuples));
        for (size_t i = 0; i < flow_edges.size(); i++) {
            (*return_tuples)[i] = flow_edges[i];
        }
        *return_count = flow_edges.size();

        pgassert(*err_msg == NULL);
        *log_msg = log.str().empty()?
            *log_msg :
            pgr_msg(log.str().c_str());
        *notice_msg = notice.str().empty()?
            *notice_msg :
            pgr_msg(notice.str().c_str());
    } catch (AssertFailedException &except) {
        (*return_tuples) = pgr_free(*return_tuples);
        (*return_count) = 0;
        err << except.what();
        *err_msg = pgr_msg(err.str().c_str());
        *log_msg = pgr_msg(log.str().c_str());
    } catch (std::exception &except) {
        (*return_tuples) = pgr_free(*return_tuples);
        (*return_count) = 0;
        err << except.what();
        *err_msg = pgr_msg(err.str().c_str());
        *log_msg = pgr_msg(log.str().c_str());
    } catch(...) {
        (*return_tuples) = pgr_free(*return_tuples);
        (*return_count) = 0;
        err << "Caught unknown exception!";
        *err_msg = pgr_msg(err.str().c_str());
        *log_msg = pgr_msg(log.str().c_str());
    }
}
