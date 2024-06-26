## *ACME S.A. Contact Management System*

### *Overview*
This project is a Contact Management System developed as a course completion project for the Data Structures subject. The system is designed to manage customer contact information efficiently, providing functionalities for inserting, searching, editing, and removing essential customer information. The project is written in C and developed using Code::Blocks.

### *Features*
- Insert New Client: Add a new client's contact information to the system.
- View All Clients: Display a complete list of all clients in the system.
- Search Client by Code: Find a client's information using their unique code.
- Search Client by Name: Locate clients based on their names.
- Edit Client Information: Update the contact details of an existing client.
- Remove Client by Code: Delete a client's information from the system using their unique code.
- Save Data Automatically: Save all client information automatically upon exiting the system.

### *Files*
- main.c: Contains the main function and the user interface logic.
- contato.c: Implements the core functionalities of the contact management system.
- contato.h: Declares the data structures and function prototypes used in the project.

### *How to Run*

*Compile the Project:*
- Open the project in Code::Blocks.
- Compile the project to generate the executable.
*Run the Executable:*
- Execute the generated binary file.
*Use the Menu:*
- Follow the on-screen menu to interact with the system.

### *Code Structure*
*main.c*
- Initializes the locale settings to Portuguese.
- Creates the contact list.
- Recovers previously saved clients from a file.
- Displays the menu and handles user inputs for various functionalities.
*contato.c*
- criaLista: Creates and initializes an empty list.
- abortaPrograma: Terminates the program with an error message.
- apagaLista: Frees the memory allocated for the list.
- tamanhoLista: Returns the number of clients in the list.
- listaVazia: Checks if the list is empty.
- coletaDados: Collects client data from the user and inserts it into the list.
- insereDados: Inserts a new client into the list in the correct order.
- exibeLista: Displays all clients in the list.
- consultaCodigo: Searches for a client by their code.
- consultaNome: Searches for clients by their name.
- editaDados: Edits the details of an existing client.
- removeDados: Removes a client from the list using their code.
- salvaDados: Saves the list of clients to a file.
*contato.h*
- CLIENTE: Structure to hold client information.
- ELEM: Node structure for the linked list.
- Lista: Pointer to the first element of the list.
- Function prototypes for all the functionalities implemented in contato.c.

### *Requirements*
- Code::Blocks IDE
- C Compiler

### *Conclusion*
This Contact Management System provides a robust platform for managing client information. It demonstrates the use of data structures, specifically linked lists, to handle dynamic data efficiently. The project serves as a practical application of concepts learned in the Data Structures course.

