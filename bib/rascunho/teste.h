int testeRemocao() {

	char* s = "rm -r /var/persist/tarefas2/dados/respostas/0/333/2222";

	int ret = system(s);

	printf("%d\n", ret);
	printf("- %d\n", WEXITSTATUS(ret));

}

/*
 * Testes realizados pelo sistema web (usuaraio www-data ou apache)
 *
 * Tentativa de apagar o diretório 2222
 *
 * Conclusão: se não houver permissão de escrita no superdiretório 333, não é possível apagar 2222. Se houver permissão de escrita no superdiretório 333, é permitida a remoção independente da permissão de escrita do supersuperdiretório 0.
 *
 * Caso 0: 333 com permissão de escrita, 2222 não existe: retorno (sys) 256, retorno (WEXITSTATUS) 1
 *
 * Caso 1: 333 com permissão de escrita, 2222 com permissão de escrita (755): apagou, retorno (sys) 0, retorno (WEXITSTATUS) 0
 *
 * Caso 2: 333 com permissão de escrita, 2222 sem permissão de escrita (555): apagou, retorno (sys) 0, retorno (WEXITSTATUS) 0
 *
 * Caso 3: 333 sem permissão de escrita (555), 2222 com permissão de escrita (755): não apagou, retorno (sys) 256, retorno (WEXITSTATUS) 1
 *
 * Caso 4: 333 sem permissão de escrita (555), 2222 com permissão de escrita (555): não apagou, retorno (sys) 256, retorno (WEXITSTATUS) 1
 *
 * Caso 5: 0 sem permissão de escrita (555), 333 com permissão de escrita, 2222 com permissão de escrita (755): apagou, retorno (sys) 0, retorno (WEXITSTATUS) 0
 *
 * Caso 6: 0 sem permissão de escrita (555), 333 com permissão de escrita, 2222 sem permissão de escrita (555): apagou, retorno (sys) 0, retorno (WEXITSTATUS) 0
 *
 * Caso 7: 0 sem permissão de escrita (555), 333 sem permissão de escrita, 2222 com permissão de escrita (755): não apagou, retorno (sys) 256, retorno (WEXITSTATUS) 1
 *
 * Caso 8: 0 sem permissão de escrita (555), 333 sem permissão de escrita, 2222 sem permissão de escrita (555): não apagou, retorno (sys) 256, retorno (WEXITSTATUS) 1
 *
 * Caso 9: 0 com permissão de escrita (755), 333 sem permissão de escrita (555), 2222 sem permissão de escrita (555): não apagou, retorno (sys) 256, retorno (WEXITSTATUS) 1
 *
 * Caso 10: 0 com permissão de escrita (755), 333 sem permissão de escrita (555), 2222 com permissão de escrita (755): não apagou, retorno (sys) 256, retorno (WEXITSTATUS) 1
 *
 * Caso 11: 0 com permissão de escrita (755), 333 com permissão de escrita (755), 2222 sem permissão de escrita (555): apagou, retorno (sys) 0, retorno (WEXITSTATUS) 0
 *
 * Caso 12: 0 com permissão de escrita (755), 333 com permissão de escrita (755), 2222 com permissão de escrita (755): apagou, retorno (sys) 0, retorno (WEXITSTATUS) 0
 *
 */
