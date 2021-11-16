create database DavidCenter;
use DavidCenter;
create table CLIENTES
( CODIGO_TICKET int auto_increment, primary key(CODIGO_TICKET),
  HORA_ENTRADA char(30),
  HORA_SAIDA char(30),
  STATUS_SAIDA char(30) not null);
  
create table TAXAS
( CODIGO_PAGAMENTO int auto_increment, primary key(CODIGO_PAGAMENTO),
  HORA_SOLICITACAO char(30),
  PRECO_TAXA float,
  CODIGO_TICKET_PAG integer,
  foreign key (CODIGO_TICKET_PAG) references CLIENTES (CODIGO_TICKET) );
  

create table VAGAS
( CODIGO_VAGA char(4) not null, primary key(CODIGO_VAGA),
  STATUS_VAGA int);
  

