#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Struct for the page so we can implement the double linked list
typedef struct Page_struct{
    int adress;
    struct Page_struct* next_page;
} Page_struct;

// Variables for handling the double linked list (page list)
int list_length = 0;
Page_struct *first_page = NULL;
Page_struct *last_page = NULL;


Page_struct *find_page_func(int adress) {
    /*
    Function to find a page with a certain adress in the list
    */
    Page_struct *current_page = first_page;
    while (current_page != NULL) {
        if (current_page->adress == adress) {
            return current_page;
        }
        current_page = current_page->next_page;
    }
    return NULL;
}

void handle_not_found_page_func(Page_struct *found_page, int no_phys_pages_int, int page_adress) {
    // Check if list is full (remove the first page if it is). The list can only be full if the list length is equal to the number of physical pages
        // This is because we only add pages to the list if they are not already in the list (i.e. we did not find the page)
        if (list_length == no_phys_pages_int) {
            Page_struct *temp = first_page;
            first_page = first_page->next_page;
            free(temp);
            list_length--;
        }
        // Create a new page and insert current adress
        Page_struct *new_page = (Page_struct*)malloc(sizeof(Page_struct));
        new_page->adress = page_adress;
        new_page->next_page = NULL;

        // If the list is empty, set the first page to the new page
        if (first_page == NULL) {
            first_page = new_page;
            last_page = new_page;
        }
        else { // If the list is not empty, set the last page's next page to the new page and set the last page to the new page
            last_page->next_page = new_page;
            last_page = new_page;
        }
}

void handle_found_page_func(Page_struct *found_page, int no_phys_pages_int, int page_adress) {
    // Move the found page to the end of the list
    if (found_page == first_page) {
        // Update the first page to the next page
        first_page = found_page->next_page;
        if (first_page == NULL) { // If list is empty after removal
            last_page = NULL;
        }
    }
    else {
        // Loop through the list to find the page before the found page
        Page_struct *prev = first_page;
        while (prev->next_page != found_page) { 
            prev = prev->next_page;
        }
        // Bypass the found page so it can be moved to the end of the list
        prev->next_page = found_page->next_page;
        if (found_page == last_page) { // Case where the found page is the last page
            last_page = prev;
        } 
    }
    // Insert the found page at the end of the list
    found_page->next_page = NULL;
    if (last_page != NULL) { // If the list is not empty
        last_page->next_page = found_page;
    }
    // Update the last page
    last_page = found_page;

    if (first_page == NULL) { // Case where the list is empty
        first_page = found_page; 
    }
}


int main(int argc, char *argv[]) {
    // Fail fast if too few arguments
    if (argc < 4) {
        // Print error message if too few arguments
        printf("To few args. Use no_phys_pages, page_size, and filename\n");
        // Return with error
        return 1;
    }

    // Grab the arguments
    char* no_phys_pages = argv[1];
    char* page_size = argv[2];
    char* filename = argv[3];

    // Convert arguments to correct types using atoi (ascii to int)
    int no_phys_pages_int = atoi(no_phys_pages);
    int page_size_int = atoi(page_size);
    // Check for invalid page size
    if (page_size_int <= 0 || no_phys_pages_int <= 0) {
        // Print error message
        printf("Invalid page size or invalid number of physical pages\n");
        // Return with error
        return 1;
    }

    // Print the first two arguments as per instructions
    printf("No physical pages = %d, page size = %d\n", no_phys_pages_int, page_size_int);

    // Print starting to read memory trace from filename as per instructions
    printf("Reading memory trace from %s... ", filename);

    // Open dat bad boi
    FILE *input_file = fopen(filename, "r");
    // Check for read error
    if (input_file == NULL) {
        // Print error message
        printf("Error reading file\n");
        // Return with error
        return 1;
    }

    // Set up remaining variables
    int num_pagefaults = 0; // Number of pagefaults
    int num_memory_references = 0; // Number of memory references
	size_t line_size = 0; // Size of line
	char *line = NULL; // Line to read

    // Read the file line by line
    while (getline(&line, &line_size, input_file) != -1) { // While there are lines to read
        // Increment number of memory references
        num_memory_references++;
        // Grab adress from line
        int current_adress = atoi(line);
        // Calculate the page adress (start of page) which is the current adress minus the remainder of the current adress divided by the page size
        int page_adress = current_adress - (current_adress % page_size_int);

        // Find the page in the list
        Page_struct *found_page = find_page_func(page_adress);
        if (found_page == NULL) { // If we did not find the page
            // Increment number of pagefaults
            num_pagefaults++;
            
            // Handle the found page
            handle_not_found_page_func(found_page, no_phys_pages_int, page_adress);

            // Increment the list length
            list_length++;
        }
        else { // Case where we did find the page
            // Handle foudn page
            handle_found_page_func(found_page, no_phys_pages_int, page_adress);
        }
    }

    // Free the line and close the file to avoid memory leaks
    free(line);
    fclose(input_file);

    // Print the number of pagefaults as per instructions
    printf("Read %d memory references\n", num_memory_references);
    printf("Result: %d page faults\n", num_pagefaults);

    // Exit with success code 0
    return 0;
}
