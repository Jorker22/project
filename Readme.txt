
    CPE 111 
    Project Progress Report
    Topic: Family Relationships System 
    Group : KGT
    Members : Tunlathon Songchay , Sarun Nuntaviriyakul 
                       Surin Hanspal

	How to use the program

    1. Select any one option out of 5 available options and these are
        1. Input data , 2. Save data , 3. Search ,4.Import , and 5. Exit.

    2. If choose 1, then input data in the form of FIRST REL LAST
        where FIRST and LAST refers to the name of the person and 
        REL refers to the relations between them. Both the name must 
        be different from each other and the input Relations in between
        them must not be any relations out of these : Father,mother,son
        daughter,sister,brother,uncle,daughter,grand father,grand mother. 
        wife and husband. If the user enter any relation other than this,
        the system will dusplay an error message .Also,the system will
        display the gender of FIRST relatively to the REL status. But we 
        haven't make a test condition for detecting Relationships error
        based on gender of FIRST.

    3.After the input of data,User can save the data by choosing Save 
       option and can exit program.
    
    4. Right now we are missing Search part . This function 
        Though have been designed up but we are not make it in use 
        because we are not sure if it's the right method or not.

      
       we have created up a source file called check.c . we tried to 
       to solve the Inter-relationships problem by firstly Taking the 
       FIRST and LAST into 2-dimensional Variable. Where our data
       going to be stored in this way 

       FIRST[0][100] Relation LAST[0][100]
       FIRST[1][100] Relation LAST[1][100]

      and so on . then we try to find out a name which exist both as a
       FIRST and LAST where only we can start to determines the 
       relationships with other member.We are not sure if we are taking 
       a right step on doing it that way. Please guide us if it's we need 
       to do it another way.We also face a problem in making both the
       variables in to 2-D as well

	Known Issue

	During save file we can only print out the last name entered the name before that become (null)  In the picture included in the zip.

