﻿//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//     Runtime Version:4.0.30319.34003
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

namespace Webserviceasmodelteste.ServiceReference1 {
    
    
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "4.0.0.0")]
    [System.ServiceModel.ServiceContractAttribute(ConfigurationName="ServiceReference1.IService1")]
    public interface IService1 {
        
        [System.ServiceModel.OperationContractAttribute(Action="http://tempuri.org/IService1/getProductsCatalog", ReplyAction="http://tempuri.org/IService1/getProductsCatalogResponse")]
        string getProductsCatalog();
        
        [System.ServiceModel.OperationContractAttribute(Action="http://tempuri.org/IService1/getProductsCatalog", ReplyAction="http://tempuri.org/IService1/getProductsCatalogResponse")]
        System.Threading.Tasks.Task<string> getProductsCatalogAsync();
        
        [System.ServiceModel.OperationContractAttribute(Action="http://tempuri.org/IService1/setDiscount", ReplyAction="http://tempuri.org/IService1/setDiscountResponse")]
        void setDiscount(int id, float discount);
        
        [System.ServiceModel.OperationContractAttribute(Action="http://tempuri.org/IService1/setDiscount", ReplyAction="http://tempuri.org/IService1/setDiscountResponse")]
        System.Threading.Tasks.Task setDiscountAsync(int id, float discount);
    }
    
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "4.0.0.0")]
    public interface IService1Channel : Webserviceasmodelteste.ServiceReference1.IService1, System.ServiceModel.IClientChannel {
    }
    
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "4.0.0.0")]
    public partial class Service1Client : System.ServiceModel.ClientBase<Webserviceasmodelteste.ServiceReference1.IService1>, Webserviceasmodelteste.ServiceReference1.IService1 {
        
        public Service1Client() {
        }
        
        public Service1Client(string endpointConfigurationName) : 
                base(endpointConfigurationName) {
        }
        
        public Service1Client(string endpointConfigurationName, string remoteAddress) : 
                base(endpointConfigurationName, remoteAddress) {
        }
        
        public Service1Client(string endpointConfigurationName, System.ServiceModel.EndpointAddress remoteAddress) : 
                base(endpointConfigurationName, remoteAddress) {
        }
        
        public Service1Client(System.ServiceModel.Channels.Binding binding, System.ServiceModel.EndpointAddress remoteAddress) : 
                base(binding, remoteAddress) {
        }
        
        public string getProductsCatalog() {
            return base.Channel.getProductsCatalog();
        }
        
        public System.Threading.Tasks.Task<string> getProductsCatalogAsync() {
            return base.Channel.getProductsCatalogAsync();
        }
        
        public void setDiscount(int id, float discount) {
            base.Channel.setDiscount(id, discount);
        }
        
        public System.Threading.Tasks.Task setDiscountAsync(int id, float discount) {
            return base.Channel.setDiscountAsync(id, discount);
        }
    }
}
