FONTES = gerador.c organizacao.c html_comum.c pagina_txt.c filtro.c

gerador: $(FONTES) pagina.h filtro.h
	gcc -Wall -Wextra -o gerador $(FONTES)

site: gerador
	./gerador site ../codigos ../txt/*.txt && cp estilo.css site/

limpar:
	rm -rf gerador site
