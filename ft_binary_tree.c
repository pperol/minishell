/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_binary_tree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pperol <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:49:49 by pperol            #+#    #+#             */
/*   Updated: 2023/03/01 15:57:10 by pperol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* allocate memory for a new node and initialize its values */
t_node	*ft_new_node(int data) 
{
	t_node *node = (t_node*)malloc(sizeof(t_node));
	node->data = data;
	node->left = NULL;
	node->right = NULL;
	/* remember to free the memory allocated for this node later */
	return (node);
}

// recursively insert a new node into the binary tree //
t_node	*ft_insert_node(t_node *root, int data) 
{
	if (root == NULL)
		return (ft_new_node(data));
	if (data < root->data)
		root->left = ft_insert_node(root->left, data);
	else if (data > root->data)
		root->right = insert(root->right, data);
	/* si égalite des priorités voir arbre non binaire ?? */
	return (root);
}

// recursively traverse the binary tree in-order and print its values. //
void ft_in_order(t_node *root)
{
	if (root == NULL)
		return ;
	ft_in_order(root->left);
	printf("%d ", root->data);
	ft_in_order(root->right);
}

/* recursively delete the entire tree and free its memory */
void ft_delete_tree(t_node *root)
{
	if (root == NULL)
		return;
	ft_delete_tree(root->left);
	ft_delete_tree(root->right);
	free(root);
}

/*Tests*/
/*
int main(void) 
{
    t_node *root;
	
	root = NULL;
	root = ft_insert_node(root, 50);
    ft_insert_node(root, 30);
    ft_insert_node(root, 20);
    ft_insert_node(root, 40);
    ft_insert_node(root, 70);
    ft_insert_node(root, 60);
    ft_insert_node(root, 80);
    ft_insert_node(root, 10);
    ft_in_order(root);
    return (0);
}
*/
