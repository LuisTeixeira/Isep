contar([],0).
contar([_|T],Tamanho):-contar(T,TamanhoSub), Tamanho is 1 + TamanhoSub.

somar([H|[]],H).
somar([H|T],Soma):- somar(T,SomaSub), Soma is H + SomaSub.

media([],"Não Existe").
media(L, Media):-somar(L,Soma),contar(L,Tamanho),Media is (Soma / Tamanho). 

menor([H|[]],H).
menor([H|T],Menor):-menor(T,M),((H < M,!, Menor is H); Menor is M).

contargama(_,_,[],0).
contargama(Maior,Menor,[H|T],NumElem):-contargama(Maior,Menor,T,NumElemSub),((H < Maior,H > Menor, NumElem is 1 + NumElemSub);NumElem is NumElemSub).