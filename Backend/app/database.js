import knex from 'knex'
import mysql from 'mysql'

/**
 * Cliente e query builder do banco de dados
 */
const db = knex({
  client: 'mysql',
  connection: {
    host: process.env.DB_HOST,
    user: process.env.DB_USER,
    password: process.env.DB_PASSWORD,
    database: process.env.DB_DATABASE
  }
})

/**
 * Classe base que representa uma fileira no banco de dados.
 * Os campos estáticos devem ser definidos nas subclasses.
 * Os métodos estáticos são usados pra adquirir/criar a fileira no banco de dados
 */
export class Row {
  /**
   * O nome da tabela no banco de dados
   */
  static table = ''
  /**
   * Chave primária, para encontrar uma fileira com o método Row.find
   */
  static primaryKey = ''
  /**
   * Os campos deste objeto que representam colunas no banco de dados
   */
  static columns = {}

  /**
   * @returns O query builder na tabela desta classe
   */
  static query() {
    return db(this.table)
  }

  /**
   * Converte os campos em colunas da tabela.
   * Exemplo na classe Vaga:
   * Entrada = { status: 0, codigo: "AAAA" }
   * Retorno = { STATUS_VAGA: 0, CODIGO_VAGA: "AAAA" }
   * @param data Objeto com campos definidos em this.columnNames
   * @returns Objeto igual ao argumento data, mas com os nomes dos parâmetros sendo os nomes das colunas
   */
  static dataToColumns(data) {
    const columns = {}
    for (const key in data) {
      if (this.columnNames[key]) columns[this.columnNames[key]] = data[key]
    }
    return columns
  }

  /**
   * Converte colunas da tabela em campos desta classe.
   * Exemplo na classe Vaga:
   * Entrada = { STATUS_VAGA: 0, CODIGO_VAGA: "AAAA" }
   * Retorno = { status: 0, codigo: "AAAA" }
   * @param data Objeto com colunas definidas em this.columnNames
   * @returns Objeto igual ao argumento columns, mas com os nomes dos parâmetros sendo os nomes dos campos
   */
  static columnsToData(columns) {
    if (Array.isArray(columns)) {
      return columns.map(c => this.columnsToData(c))
    }

    const data = new this()
    for (const key in columns) {
      const dataKey = Object.keys(this.columnNames).find(name => this.columnNames[name] == key)
      if (dataKey) data[dataKey] = columns[key]
    }
    return data
  }

  /**
   * Equivalente de "SELECT * FROM..."
   * @returns Array com fileiras
   */
  static async all() {
    const rows = await db(this.table).select('*')
    const models = rows.map(row => new this(this.columnsToData(row)))

    return models
  }

  /**
   * Equivalente de "SELECT * FROM ... WHERE (chave primaria) = value"
   * @returns Fileira
   */
  static async find(value) {
    const row = (
      await db(this.table)
        .select('*')
        .where({ [this.primaryKey]: value })
    )[0]
    const data = this.columnsToData(row)
    const model = new this(data)

    return model
  }

  /**
   * Equivalente de "INSERT NTO ... VALUES (data)"
   * @returns Fileira
   */
  static async create(data) {
    const columns = this.dataToColumns(data)

    const pk = await db(this.table).insert(columns)
    const pkData = this.columnsToData({ [this.primaryKey]: pk[0] })
    data = Object.assign(data, pkData)

    const model = new this(data)

    return model
  }

  /**
   * Equivalente de UPDATE
   * @param data Fileira
   */
  static async save(data) {
    const columns = this.dataToColumns(data)
    const row = await db(this.table)
      .where({ [this.primaryKey]: columns[this.primaryKey] })
      .update(columns)
  }

  constructor(data) {
    for (const key in data) {
      this[key] = data[key]
    }
  }
}

export class Vaga extends Row {
  static table = 'vagas'
  static primaryKey = 'CODIGO_VAGA'
  static columnNames = {
    codigo: 'CODIGO_VAGA',
    status: 'STATUS_VAGA'
  }
}

export class Pagamento extends Row {
  static table = 'pagamentos'
  static primaryKey = 'CODIGO_PAGAMENTO'
  static columnNames = {
    codigo: 'CODIGO_PAGAMENTO',
    hora: 'HORA_SOLICITACAO',
    preco: 'PRECO_TAXA',
    codigoTicket: 'CODIGO_TICKET_PAG'
  }

  validExit() {
    const tolerancia = 1000 * 60 * 15 // 15 minutos de tolerância para a saída

    return Date.now() - this.hora.getTime() < tolerancia
  }
}

export class Ticket extends Row {
  static table = 'tickets'
  static primaryKey = 'CODIGO_TICKET'
  static columnNames = {
    codigo: 'CODIGO_TICKET',
    horaEntrada: 'HORA_ENTRADA',
    horaSaida: 'HORA_SAIDA',
    statusSaida: 'STATUS_SAIDA'
  }
}



export default db
