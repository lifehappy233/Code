from SimpleXMLRPCServer import SimpleXMLRPCServer   
def respon_string(str):
    return "get string :%s"%str

if __name__ == '__main__':
    s = SimpleXMLRPCServer(('0.0.0.0', 8080))
    s.register_function(respon_string,"get_string")
    s.serve_forever()
