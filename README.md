# evalunidad4-re_xd
evalunidad4-re_xd created by GitHub Classroom

El código funcionará teniendo el Productor, que en este caso es un hospital llamado Sara Tobón Uribe, que contará con una cantidad límitada de doctores, el
Consumidor que serían los pacientes, que se categorizarán en 3 diferentes tipos de enfermedades y algunos podrán requerir de más citas de atención 
y contará con 2 buffers.

El sentido irá de esta manera, el hospital va a empezar a generar sus contratos a doctores con especialidades especificas y van a tener en stand-by a esos 
doctores, luego les va a asignar un consultorio en el que van a esperar a los pacientes, de ahí los pacientes, dependiendo de la enfermedad que tengan, van a
tomar una cita con el doctor que necesitan, de ahí el doctor con el paciente hacen el procedimiento y termina la cita, el doctor de ahí se va a esperar que el
hospital le asigne otro consultorio para dar otra cita; y así sucesivamente.

La persona que esté en consola podrá hacer de recepcionista para los pacientes, entonces el programa le preguntará por el nombre, edad, y 
la enfermedad que está padeciendo, de ahí el programa creará el hilo para ese paciente y de ahí se generará todo el procedimiento.

El hospital estará pre-creado, los doctores igualmente, el hospital empezará teniendo los consultorios llenos, de ahí la persona en consola creará los 
hilos de los pacientes, cada paciente tomará al doctor especifíco que necesita, harán el procedimiento y después de la cita, el doctor entrará a un buffer stand-by
hasta que el hospital le asigne otro consultorio.
