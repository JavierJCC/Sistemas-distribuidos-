//
// Cliente.java
//
package hola;

// Importamos las clases de CORBA necesarias
import org.omg.CORBA.ORB;

// Importamos otras clases necesarias de Java
import java.io.*;
public class Cliente {
public static void main (String args[ ]) {

	try {
		// INICIAMOS ORB
		ORB orb = ORB.init(args, null);

		// LEEMOS EN ARCHIVO UBICACION DEL OBJETO REMOTO
		FileInputStream file = new FileInputStream("hola.ref");
		BufferedReader in = new BufferedReader(new InputStreamReader(file));
		String ref = in.readLine();

		// CREAMOS REFERENCIA AL OBJETO REMOTO
		holamundo h = holamundoHelper.narrow(orb.string_to_object(ref));

		// UNA VEZ OBTENIDA LA REFERENCIA PODEMOS LLAMAR
		// A LOS METODOS DEL OBJETO REMOTO
		h.saludo();

	} catch(Exception e) {
		System.out.println("ERROR : " + e);
		e.printStackTrace(System.out);
	}
}
}

