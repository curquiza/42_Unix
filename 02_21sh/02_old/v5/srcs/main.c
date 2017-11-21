/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 16:44:40 by curquiza          #+#    #+#             */
/*   Updated: 2017/05/28 00:04:33 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_read_command_newline(char **line)
{
	char	*tmp;

	//tmp = *line;
	ft_strdel(line);
	if (get_next_line(0, line) != 1)
	{
		*line = ft_strjoin(NULL, "\n");
		return ;
	}
	//free(tmp);
	tmp = *line;
	*line = ft_strjoin(tmp, "\n");
	free(tmp);
}

/*
** DEROULEMENT DU SHELL :
**
** 1) lexer : on sépare la chaine de char envoyée par l'utilisateur en token
** (càd en mots) et on identifie le type de token, si possible.
** ex : opérateur de contrôle, io_number, word...
**
** 2) parser : on verifie les erreurs de syntax + on gere les inhibiteurs (le
** shell attend le retour de l'user) + on recupere les arguments des here-docs.
** Cf shell grammar pour les hdocs.
**
** 3) ast : on construit l'abstract syntax tree. Les noeuds sont des opérateurs
** de controle et les feuilles des commandes simples.
**
** 4) expansion : on gère les expansions, càd dans mon cas pour l'instant la
** parameter expansion (en mode bébé) et la removal quotes (simple quote,
** double quote et back-slash). Cf shell grammar.
**
** 5) semantic_analysis : dans l'ast, à l'intérieur de chaque feuille (= les
** commandes simples) on split les tokens en differents roles : assigment words,
** commande, arguments, ou redirection.
** Dans cette partie, pour faciliter la future execution, on crée un **char pour
** stocker les arguments, et on re-organise les redirections dans une liste
** chainée adaptée.
**
** 6) execution : on execute la totalité des commandes de l'ast.
*/

int		main(int ac, char **av, char **environ)
{
	t_lexeme	*lex;
	t_ast		*ast;
	t_shell		*shell;
	char		*line;

	(void)ac;
	(void)av;
	shell = ft_init_shell(environ);
	
	line = NULL;
	while (shell->run == 1)
	{
		lex = NULL;
		ast = NULL;
		ft_putstr_col("21sh> ", GREEN, DEF);
		ft_read_command_newline(&line);
		ft_lexer(&lex, line); // ETAPE 1
		if (ft_parser(&lex, shell) == 0) // ETAPE 2
		{
			ft_ast(lex, &ast, shell); // ETAPE 3
			ft_expansion(ast); // ETAPE 4

			ft_putendl("\n---- AST -----\n");
			ft_putast(ast, 0, 0);
			ft_putast_2(ast);
			ft_putendl("--------------\n");

			ft_semantic_analysis(ast); // ETAPE 5
			ft_cmd_line_execution(&ast, shell);
		}
		else
		{
			ft_chg_varval_or_add(&shell->var_priv, "?", "258");
			ft_lexlstdel(&lex);
		}
		ft_putendl2_fd("\n--------------\n\nret cmd = ", ft_get_varvalue(shell->var_priv, "?"), 1);
	}
	return (0);
}

//main amelioré
/*int 	main()
{
	t_lexeme	*lex;
	t_ast		*ast;
	t_shell		*shell;
	char		*line;
	int			ret_parser;

	shell = ft_init_shell(environ, ac, av); //gestion des flags
	line = NULL;
	while (shell->run == 1)
	{
		lex = NULL; //bien laisser et ne PAS mettre dans ft_lexer
		//ast = NULL; //pas besoin car dans ft_ast
		ft_putstr_col("21sh> ", GREEN, DEF);
		ft_read_command_newline(&line);
		ft_lexer(&lex, line);
		ret_parser = ft_parser(&lex, shell)
		ft_ast(lex, &ast, shell);
		//gestion evetnuelle de l'aff de l'arbre
		ft_cmd_line_execution(&ast, shell, ret_parser, lex);
		// DANS FT_CMD_LINE
			//ft_chg_varval_or_add(&shell->var_priv, "?", "258");
			//ft_lexlstdel(&lex);
	}
}*/
