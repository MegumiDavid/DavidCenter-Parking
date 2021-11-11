const express = require('express')
const bodyParser = require('body-parser')
const app = express()
const port = 3000

var mysql = require('mysql');
var con = mysql.createConnection({
  host: "localhost",
  user: "root",
  password: "password",
  database: 'davidcenter'
});
con.connect(function(err) {
  if (err) throw err;
  console.log("Connected!");
});

app.set('view engine', 'ejs')
app.use(bodyParser.urlencoded({extended:true}))
app.use(express.static('public'))





app.get('/vagas', function(req,res){

    let statusAndar = '* O segundo piso possui mais vagas disponíveis! (estatico)'
    // livre
    var sql_livre = 'select CODIGO_VAGA from davidcenter.vagas where STATUS_VAGA in (0);'
    var vagaLivre = 0
    con.query(sql_livre, function(err, result){
        if(err) throw err;
        vagaLivre = result.length;
    })

    // ocupado
    var sql_ocupado = 'select CODIGO_VAGA from davidcenter.vagas where STATUS_VAGA in (1);'
    var vagaOcupada = 0
    con.query(sql_ocupado, function(err, result){
        if(err) throw err;
        vagaOcupada = result.length;
    })

// Ver o melhor Andar - not working yet
// var andar = [1,2,3,4,5]

// function melhor_andar(){
//     var list = [];
//     for(var i=0;i<andar.length;i++){
//         var sql_andar = `select CODIGO_VAGA from davidcenter.vagas where STATUS_VAGA in (0) and CODIGO_VAGA like '${andar[i]}%';`
//         con.query(sql_andar, function(err, result){
//             if(err) throw err;
//             let andar_num = result.length;
//             list.push(andar_num);
//         })
//     }
//     return list;
// }
// var x = melhor_andar()

    res.render('vagas', {vagaLivre: vagaLivre  , vagaOcupada:vagaOcupada, statusAndar:statusAndar});
})

app.listen(port, function(){
    console.log(`Server started on port ${port}`)
})