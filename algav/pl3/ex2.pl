cor(ceu,azul).
cor(ceu,cinzento).
cor(ceu,preto).
cor(mar,azul).
cor(mar,verde).
cor(mar,cinzento).
cor(via,cinzenta).
cor(via,castanha).
cor(via,preta).

transporte(ceu,aviao).
transporte(ceu,foguete).
transporte(ceu,helicopetro).
transporte(mar,navio).
transporte(mar,lancha).
transporte(via,carro).
transporte(via,camiao).
transporte(via,mota).
transporte(via,autocarro).

nega(Predicado):-call(Predicado),!,fail;true.
se_entao_senao(Predicado, Se, Senao):-call(Predicado),!,call(Se);call(Senao).
se_entao(Predicado,Se):-call(Predicado),!,call(Se);true.

questao(Valor):-write('Qual é o atributo? '),read(Atr),append([],[Atr],L1),write(L1),
		write('Qual é o objecto? '),read(Obj),append(L1,[Obj],L2),
		repeat, write('Qual é a cor do objecto? '),read(Valor),append(L2,[Valor],L3),
		Predicado=..L3, call(Predicado).