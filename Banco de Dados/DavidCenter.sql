create table CLIENTES
( CODIGO_TICKET number (8) constraint PK_CODIGO_TICKET primary key,
  HORA_ENTRADA varchar2(30),
  HORA_SAIDA varchar2(30),
  STATUS_SAIDA varchar2(30));
  
create table TAXAS
( CODIGO_PAGAMENTO number (8) constraint PK_CODIGO_PAGAMENTO primary key,
  HORA_SOLICITACAO varchar2(30),
  PRECO_TAXA number(10),
  CODIGO_TICKET_PAG number (8),
  foreign key (CODIGO_TICKET_PAG) references CLIENTES (CODIGO_TICKET) );
  

  
create table VAGAS
( CODIGO_VAGA varchar2 (4) constraint PK_CODIGO_VAGA primary key,
  STATUS_VAGA number(2));
  
