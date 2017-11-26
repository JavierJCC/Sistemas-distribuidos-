//
// Cliente.java
//
package calculadora;

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
		calculadoramundo h = calculadoramundoHelper.narrow(orb.string_to_object(ref));

		// UNA VEZ OBTENIDA LA REFERENCIA PODEMOS LLAMAR
		// A LOS METODOS DEL OBJETO REMOTO
		h.saludo();
		System.out.printf("\t\tCALCULADORA DE NUMEROS ENTEROS\n");
		System.out.printf("El resultado de sumar 8+8 es: %d \n",h.suma(8,8));
		System.out.printf("El resultado de restar 9-1 es: %d\n",h.resta(9,1));
		System.out.printf("El resultado de dividir 8/8 es: %d\n",h.divi(8,8));
		System.out.printf("El resultado de multiplicar 8*8 es: %d\n",h.multi(8,8));

	} catch(Exception e) {
		System.out.println("ERROR : " + e);
		e.printStackTrace(System.out);
	}
}
}

