create database DavidCenter;
use DavidCenter;
create table TICKETS
( CODIGO_TICKET int auto_increment, primary key(CODIGO_TICKET),
  HORA_ENTRADA datetime,
  HORA_SAIDA datetime,
  STATUS_SAIDA char(30) not null);
  
create table PAGAMENTOS
( CODIGO_PAGAMENTO int auto_increment, primary key(CODIGO_PAGAMENTO),
  HORA_SOLICITACAO datetime,
  PRECO_TAXA float,
  CODIGO_TICKET_PAG integer,
  foreign key (CODIGO_TICKET_PAG) references CLIENTES (CODIGO_TICKET) );

create table VAGAS
( CODIGO_VAGA char(4) not null, primary key(CODIGO_VAGA),
  STATUS_VAGA int);
