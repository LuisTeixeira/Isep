using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Web;

namespace Webserviceasmodelteste.Models
{
    public class Book
    {
       
        public int id;
        public string name;
        [DataType(DataType.Currency)]
        public decimal price;
    }
}