
var xmlHttpObj;

function CreateXmlHttpRequestObject() {
    //Detecção de browser simplificada sem tratamento de excepções
    xmlHttpObj = null;

    if (window.XMLHttpRequest) {
        xmlHttpObj = new XMLHttpRequest();
    } else if (window.ActiveXObject) {
        xmlHttpObj = new ActiveXObject("Microsoft.XMLHTTP");
    }
    return xmlHttpObj;
}

function MakeXMLHTTPCall() {
    xmlHttpObj = CreateXmlHttpRequestObject();

    if (xmlHttpObj) {
        //Definição do URL para efectuar pedido HTTP

        xmlHttpObj.open("GET", "serveXml.php", true);

        //Registo do EventHandler
        xmlHttpObj.onreadystatechange = stateHandler;
        xmlHttpObj.send(null);
    }

    function stateHandler(){
        if (xmlHttpObj.readyState === 4 && xmlHttpObj.status === 200) {
            // resposta do servidor completa
            // propriedade responseXML que devolve a resposta do servidor
            var docxml = xmlHttpObj.responseXML;
            
            var divResults = document.getElementById("divResults");
            divResults.innerHTML = "";
            
            var tableElement = document.createElement("table");
            divResults.appendChild(tableElement);
            
            var firstNameHeader = document.createElement("th");
            firstNameHeader.innerHTML = "First Name";
            tableElement.appendChild(firstNameHeader);
            var lastNameHeader = document.createElement("th");
            lastNameHeader.innerHTML = "Last Name";
            tableElement.appendChild(lastNameHeader);
            var emailHeader = document.createElement("th");
            emailHeader.innerHTML = "E-mail";
            tableElement.appendChild(emailHeader);
            
            // lista de nós com Tag Firstname
            var nodelist = docxml.getElementsByTagName("Customer");
            

            for(var i = 0; i < nodelist.length; i++){
                var firstName = nodelist[i].getElementsByTagName("Firstname")[0].childNodes[0].nodeValue;
                var lastName = nodelist[i].getElementsByTagName("Lastname")[0].childNodes[0].nodeValue;
                var email = nodelist[i].getElementsByTagName("email")[0].childNodes[0].nodeValue;
                
                var trElement = document.createElement("tr");
                tableElement.appendChild(trElement);
                
                var firstNameNode = document.createElement("td");
                firstNameNode.innerHTML = firstName;
                trElement.appendChild(firstNameNode);
                
                var lastNameNode = document.createElement("td");
                lastNameNode.innerHTML = lastName;
                trElement.appendChild(lastNameNode);
                
                var emailNode = document.createElement("td");
                emailNode.innerHTML = email;
                trElement.appendChild(emailNode);
            }
        }
    }
}


