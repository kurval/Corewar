/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar_error.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkonjuha <bkonjuha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 15:39:30 by bkonjuha          #+#    #+#             */
/*   Updated: 2020/09/16 22:32:52 by bkonjuha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_ERROR_H
# define COREWAR_ERROR_H

# define VM_ERROR "ERROR: Can't initialize Virtual Machine"

# define ARENA_ERROR "ERROR: Can't initialize Arena"

# define INPUT_ERROR "ERROR: Invalid input parameter"

# define OPEN_ERROR "ERROR: Can't open the file"

# define CHAMP_ERROR "ERROR: Invalid Champion"

# define CHAMP_NUM_ERROR "ERROR: Too many champions"

# define N_FLAG_ERROR "ERROR: -n flag number out of bounds"

# define N_FLAG_INPUT "ERROR: invalid -n flag input paramaters"

# define DUMP_ERROR "ERROR: -Dump invalid dump flag"

# define DUPLICATE_N "ERROR: Champion ID already in use"

# define DUMP_ERROR_SET "ERROR: Dump already set"

# define NB_PROCS_ERROR "ERROR: Too many processes"

# define MALLOC_ERROR "ERROR: Malloc failed"

# define MAGIC_ERROR "ERROR: Invalid magic header"

# define SPACE_ERROR "ERROR: Missing whitespace"

# define SIZE_ERROR "ERROR: Code size does not match the given size"

# define CODE_ERROR "ERROR: The code size differs from what its header says"

#endif
