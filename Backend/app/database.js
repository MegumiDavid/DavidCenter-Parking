import knex from 'knex'

const db = knex({
  client: 'mysql',
  connection: {
    host: process.env.DB_HOST,
    user: process.env.DB_USER,
    password: process.env.DB_PASSWORD,
    database: process.env.DB_DATABASE
  }
})

export class Model {
  static table = ''
  static primaryKey = ''
  static columns = {}

  static dataToColumns(data) {
    const columns = {}
    for (const key in data) {
      if (this.columnNames[key]) columns[this.columnNames[key]] = data[key]
    }
    return columns
  }

  static columnsToData(columns, columnNames) {
    const data = {}
    for (const key in columns) {
      const dataKey = Object.keys(this.columnNames).find(name => this.columnNames[name] == key)
      if (dataKey) data[dataKey] = columns[key]
    }
    return data
  }

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

  static async create(data) {
    const columns = this.dataToColumns(data)

    const pk = await db(this.table).insert(columns)
    const pkData = this.columnsToData({ [this.primaryKey]: pk[0] })
    data = Object.assign(data, pkData)

    const model = new this(data)

    return model
  }

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

export class Vaga extends Model {
  static table = 'vagas'
  static primaryKey = 'CODIGO_VAGA'
  static columnNames = {
    codigo: 'CODIGO_VAGA',
    status: 'STATUS_VAGA'
  }
}

export class Taxa extends Model {
  static table = 'taxas'
  static primaryKey = 'CODIGO_PAGAMENTO'
  static columnNames = {
    codigo: 'CODIGO_PAGAMENTO',
    hora: 'HORA_SOLICITACAO',
    preco: 'PRECO_TAXA',
    codigoTicket: 'CODIGO_TICKET_PAG'
  }
}

export class Cliente extends Model {
  static table = 'clientes'
  static primaryKey = 'CODIGO_TICKET'
  static columnNames = {
    codigo: 'CODIGO_TICKET',
    horaEntrada: 'HORA_ENTRADA',
    horaSaida: 'HORA_SAIDA',
    statusSaida: 'STATUS_SAIDA'
  }
}

export default db
