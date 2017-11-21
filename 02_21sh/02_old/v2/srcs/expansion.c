#include "shell.h"

void	ft_expansion(t_ast *ast, t_var *tabvar)
{
	t_lexeme	*current;

	if (ast)
	{
		current = ast->lex;
		while (current)
		{
			if (current->token == WORD || current->token == ASS_WORD)
			{
				ft_parameter_expansion(&current->s, tabvar);
				ft_quote_removal(&current->s);
			}
			current = current->next;
		}
		ft_lexlst_remove_if(&ast->lex, "", 0);
		if (ast->left)
			ft_expansion(ast->left, tabvar);
		if (ast->right)
			ft_expansion(ast->right, tabvar);
	}
}
