cor(céu, azul). 
cor(céu, cinzento). 
cor(céu, preto). 
cor(mar, azul). 
cor(mar, verde). 
cor(mar, cinzento). 
cor(via, cinzenta). 
cor(via, castanha). 
cor(via, preta). 
 
transporte(céu,avião). 
transporte(céu,helicóptero). 
transporte(céu,foguete). 
transporte(mar,navio). 
transporte(mar,lancha). transporte(via,carro). 
transporte(via,camião). 
transporte(via,mota). 
transporte(via,autocarro). 

nega(P):- call(P), !, fail ; true.
ifthenelse(C,T,F):-
	call(C), !, call(T)
	;
	call(F) , ! , fail.

ithen(C,T):-
	call(C), !, call(T) ; true.

questao(Valor):-
	write('Atributo:'), read(A) ,
	write('Objeto:'),   read(O) ,
	repeat ,
	write('Qual o(a) '), write(A),
	write(' do(a) '),    write(O), write('?'),
	read(Valor),
	append([], [A, O, Valor], Lista), 
	Pre=..Lista,
	call(Pre), !.
