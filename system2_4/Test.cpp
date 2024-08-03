#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "node.hpp"
#include "tree.hpp"

using namespace std;

TEST_CASE("general tests") 
{
    Node<double> root_node = Node<double>(1.1);
    Tree<double> tree; // Binary tree that contains doubles.
    tree.add_root(root_node);
    Node<double> n1(1.2);
    Node<double> n2(1.3);
    Node<double> n3(1.4);
    Node<double> n4(1.5);
    Node<double> n5(1.6);

    tree.add_sub_node(root_node, n1);
    tree.add_sub_node(root_node, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);                

    vector<double> pre_order_expected = {1.1, 1.2, 1.4, 1.5, 1.3, 1.6};
    vector<double> post_order_expected = {1.4, 1.5, 1.2, 1.6, 1.3, 1.1};
    vector<double> in_order_expected = {1.4, 1.2, 1.5, 1.1, 1.6, 1.3};
    vector<double> bfs_expected = {1.1, 1.2, 1.3, 1.4, 1.5, 1.6};
    vector<double> dfs_expected = {1.1, 1.2, 1.4, 1.5, 1.3, 1.6};

    size_t i = 0;
    for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node, ++i) {
        CHECK_EQ((*node)->get_value(), pre_order_expected[i]);
    }

    i = 0;
    for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node, ++i) {
        CHECK_EQ((*node)->get_value(), post_order_expected[i]);
    }

    i = 0;
    for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node, ++i) {
        CHECK_EQ((*node)->get_value(), in_order_expected[i]);
    }

    i = 0;
    for (auto node = tree.begin_bfs(); node != tree.end_bfs(); ++node, ++i) {
        CHECK_EQ((*node)->get_value(), bfs_expected[i]);
    }

    i = 0;
    for (auto node = tree.begin_dfs(); node != tree.end_dfs(); ++node, ++i) {
        CHECK_EQ((*node)->get_value(), dfs_expected[i]);
    }

    i = 0;
    for (auto node : tree) {
        CHECK_EQ(node->get_value(), bfs_expected[i++]);
    }
}


