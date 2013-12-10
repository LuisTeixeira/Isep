using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using System.Web.Script.Serialization;
using Webserviceasmodelteste.Models;

namespace Webserviceasmodelteste.Controllers
{
    public class HomeController : Controller
    {
        //
        // GET: /Home/
        ServiceReference1.Service1Client Client = new ServiceReference1.Service1Client();

        public ActionResult Index()
        {
            string JSONBooks = Client.getProductsCatalog();
            JavaScriptSerializer ser = new JavaScriptSerializer();
            List<Book> books = ser.Deserialize<List<Book>>(JSONBooks);
            return View(books);
        }

        public ActionResult Details(int id)
        {
            string JSONBooks = Client.getProductsCatalog();
            JavaScriptSerializer ser = new JavaScriptSerializer();
            List<Book> books = ser.Deserialize<List<Book>>(JSONBooks);
            var obj = from b in books where b.id == id select new Book { id = b.id, name = b.name, price = b.price};
            Book book = (Book)obj.First();
            return View(book);
        }

    }
}
