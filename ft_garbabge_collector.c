/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_garbabge_collector.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pperol <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 11:40:11 by pperol            #+#    #+#             */
/*   Updated: 2023/03/02 11:56:39 by pperol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	*ft_gc_malloc(t_gc_node **head, size_t size) 
{
    void		*addr;
	t_gc_node	*node;


	addr = malloc(size); // allocate memory using standard malloc function
    if (addr == NULL) 
	{
        // handle error if malloc fails to allocate memory
        printf("Error: failed to allocate memory\n");
        exit(1);
    }
    // create a new node for the garbage collector
    node = malloc(sizeof(struct gc_node));
    if (node == NULL)
	{
        // handle error if malloc fails to allocate memory for the gc node
        printf("Error: failed to allocate memory\n");
        exit(1);
    }
    // set the fields of the gc node
    node->addr = addr;
    node->size = size;
    node->is_marked = 1;
    node->next = *head;
    *head = node; // update the head of the linked list
    return (addr); // return the address of the allocated memory
}

