//
// Servidor.java
//
package hola;

// IMPORTAMOS LAS CLASES DE CORBA NECESARIAS
import org.omg.CORBA.ORB;
import org.omg.PortableServer.*;
import org.omg.PortableServer.POA;

// *****************************************************
// IMPLEMENTACION DE LOS METODOS REMOTOS

// *****************************************************
class holamundoImplementacion extends holamundoPOA
{
	public void saludo()
	{
	System.out.println("Hola Mundo!!\n");
	}
}

// *******************************************************************************
// PROGRAMA SERVIDOR: RECIBE PETICIONES Y LAS ENVÍA A LOS DELEGADOS
// SIMILAR PARA CUALQUIER PROGRAMA SERVIDOR QUE USE CORBA
// *******************************************************************************
public class Servidor {
public static void main (String args[ ]) {

	try {
		// INICIAMOS ORB Y POA
		ORB orb = ORB.init(args, null);
		POA rootPOA = POAHelper.narrow(orb.resolve_initial_references("RootPOA"));
		rootPOA.the_POAManager().activate();

		// CREAMOS LOS OBJETOS QUE DARAN SERVICIO
		// Y LOS CONECTAMOS AL ORB
		holamundoImplementacion holaIMPL = new holamundoImplementacion();
		holamundo hh = holaIMPL._this(orb);

		// CREAMOS UNA CADENA CON LA IDENTIFICACION DEL OBJETO
		String ref = orb.object_to_string(hh);

		// VOLCAMOS LA IDENTIFICACION A UN ARCHIVO PARA
		// PERMITIR AL CLIENTE HALLAR EL OBJETO REMOTO
		java.io.FileOutputStream file = new java.io.FileOutputStream("hola.ref");
		java.io.PrintWriter out = new java.io.PrintWriter(file);
		out.println(ref);
		out.flush();
		file.close();

		// ESPERAMOS INVOCACIONES DE LOS CLIENTES
		orb.run();

	} catch(Exception e) {
		System.out.println("ERROR : " + e);
		e.printStackTrace(System.out);
	}
}
}
