# LibraryManagement
* GUI - Zach
* Backend - Alex

## User  
class
### Data  
* Name : string
* U-card number : int (?)
* Address : string
* Telephone : int
* Books checked out : Book[6]

### Functions  
* Search system for book
* Reserve item
* Set reminder 3 days before due

### Other info
* can borrow up to 6 items (non-staff) or 12 items (staff)

## Book  
struct
### Data  
* Title : string
* Author : string
* ISBN : int
* Number of copies : int
* longTerm : bool

## Staff : public Users
class
### data
* Books checked out : Book[12]

## Assistant : public Staff
class
### Functions  
* Borrow book
* Return book

## Manager : public Assistant
class
### Functions  
* Add book  
  * Add Copy
* Edit book
* Remove book
* Add users
* Remove users
* edit users

## Library
class
### Data
* Book database : vector\<Book\>
* RegisteredUsers : vector\<Users\>
* StaffMembers : vector\<Staff\>
* CheckedOutBooks : vector\<BookReciept\> (sorted by closest due date)
* currentDate : Date
* BookReciept { U-Number, ISBN } : struct
### Functions
* Add / Remove / Edit
  * Authenticate manager and assistant here
* Checkout
  * Set reminder here
  * Set due date here
  * Authenticate?
* Authenticate
  * __TARGET_CLASS__ == dyanmic_cast\<Staff\>(__STAFF_DERIVED_CLASS__)
  
  ## Misc info
* Some books are short term (1-week loan)
* Others are long term (4-week)
* New books and copies arrive regularly and old books are sometimes disposed of 
* Authenticate mananger and assistant
