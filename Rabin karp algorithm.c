#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define d 10

char* dictionary(char search[], char line[], int q) 
{
    //Finding length of both strings
    int m = strlen(search);
    int n = strlen(line);
    int i, j;
	int p=0; //hash value for pattern
	int t=0; //hash value for txt
	int h=1;
	static char pattern[20];
	//the value of h would be pow(d,M-1)%q
    for (i = 0; i < m - 1; i++)
    {
  	  h = (h * d) % q;
    }
    // Calculating hash value for pattern and first window of text
    for (i = 0; i < m; i++)
    {
       p = (d * p + search[i]) % q;  //8
       t = (d * t + line[i]) % q;   //7
    }
    // Finding the match
    for (i = 0; i <= n - m; i++) 
	{
        if (p == t) 
		{
			//check for characters one by one
            for (j = 0; j < m; j++)
		   {
             if (line[i + j] != search[j])
             break;
           }
           if (j == m)
           {
           	for (j = 0; j < m; j++)
		   {
             pattern[j]=search[j];
           }
           pattern[j]='\0';

            return pattern;  
		}
       }
       if (i < n - m) 
	   {
          t = (d * (t-line[i] * h) + line[i + m]) % q;
		  if (t < 0)
          t = (t + q);
          
       }
       else 
       return "error";
    }
}
int* stringsearch(char pattern[], char text[], int q) {
  int m = strlen(pattern);
  int n = strlen(text);
  int i, j;
  int p = 0;
  int t = 0;
  int h = 1;

  for (i = 0; i < m - 1; i++)
    h = (h * d) % q;

  for (i = 0; i < m; i++) {
    p = (d * p + pattern[i]) % q;
    t = (d * t + text[i]) % q;
  }
  for (i = 0; i <= n - m; i++) {
    if (p == t) {
      for (j = 0; j < m; j++) {
        if (text[i + j] != pattern[j])
          break;
      }

      if (j == m)
        return i+1;
        
    }
    if (i < n - m) {
      t = (d * (t - text[i] * h) + text[i + m]) % q;

      if (t < 0)
        t = (t + q);
    }
  }
}

int main()
{
	int q=26, opt, m;
	char line[100], meaning[100], search[20];
	char *word;
	int *p;
	char ch;
	FILE *fp;
	printf("\t\tWelcome to our program");
	
	do{
		printf("\nwhat function you want to perform ? ");
	printf("\n1.String searching");
	printf("\n2.Dictionary\n");
	scanf("%d", &opt);
	
	switch(opt)
	{
		case 1:{
			printf("Enter pattern you want to search\n");
            scanf(" %s", search);
            FILE *ptr;
            ptr=fopen("string.txt","r");
			fgets(line,1000,ptr);
            int p=stringsearch(search, line, q);
            printf("Pattern is found at position:  %d \n",p );
            fclose(ptr);
			break;
		}
		case 2: {
			printf("Enter word: ");
        	scanf("%s", search);
	
        	fp=fopen("f2.txt", "r"); // reading file
        	
        	for(;!feof(fp);)  // access the whole file
	        {
			fgets(line,100,fp); // storing one line of a file in an array

			
            word= dictionary(search,line,q);

			if(strcmp(word,search)==0)  // comparing the words
			{
				printf("\nWord: %s", word);
				int a=strlen(word);
				for(int i=a,j=0;;i++,j++)
        	{
	            	if((line[i])=='\0')
	            	{
	            		break;
	             	}
	             	else 
	            	{
	            		meaning[j]=line[i];
	            		m=j;
	            	}
	        }
	        meaning[m]='\0';
	    	printf("\nMeaning: %s", meaning);
			break;
	    	}
	        }
            	if(strcmp(search,word)!=0)
              	{
               		printf("\nSorry, entered string is not present.");
             	}

                	fclose(fp); //closing file
	        		break;
		}
		
		default:
			printf("\nError! invalid input");
	}
	printf("\nDo you want to continue ? (Y-yes || N-no)\n");
	scanf(" %c", &ch);
	}while(ch=='Y' || ch=='y');
	
		
	return 0;
}