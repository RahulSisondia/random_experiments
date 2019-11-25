#ifndef MOBILE_BANKING_INCLUDED
#define MOBILE_BANKING_INCLUDED

#include <cstdint>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

enum class Customer_type { Pre_paid, Post_paid };
/*
 Abstract class for Customer's information.
*/
class Customer {
 public:
  /*
    Factory Method that creates a concrete object from Customer hierarchy

    @param
        name			[in]	name of the customer
    mob_number		[in]	mobile number of customer
    call_duration	[in]	Duratation of the call allowed for post paid
    customer balance	[in]	Balance of pre-paid customer
        customer_type	[in]	Type of customer.
  */
  static std::unique_ptr<Customer> create(const std::string& name,
                                          const std::string& mob_number,
                                          const uint32_t call_duration,
                                          const uint32_t balance,
                                          Customer_type type);

  /* attributes */
  virtual bool credit(uint32_t amount) = 0;

  /* Getter methods for customer information */
  uint64_t get_id();
  Customer_type get_type();
  std::string get_mob_number();
  std::string get_name();
  uint32_t enquire_balance();
  uint32_t enquire_call_duration();

  virtual ~Customer();
  friend std::ostream& operator<<(std::ostream& os, const Customer& customer);

 protected:
  Customer(const std::string& name, const std::string& mob_number,
           const uint32_t call_duration, const uint32_t m_balance,
           Customer_type type);

  std::string m_name;       /* Name of the customer */
  std::string m_mob_number; /* Mobile number of the  customer */
  uint32_t m_call_duration; /* Call duration */
  uint32_t m_balance;       /* current balance of the customer */
  uint64_t m_customer_id;   /* Unique ID of customer within its category */
  Customer_type m_type;    /* Customer type e.g. Postpaid or Prepaid */
};

class Prepaid_customer : public Customer {
 public:
  Prepaid_customer(const std::string& name, const std::string& mob_number,
                   const uint32_t call_duration, const uint32_t balance,
                   Customer_type type);
  ~Prepaid_customer();

  bool credit(uint32_t amount) override;

 private:
  bool recharge(uint32_t amount);
  /*
    At the moment this will always be a simple integer counter.
    We may improve it in following two ways :
    -  by making it alpanumeric counter
    -  by reusing the old ids
  */
  static uint64_t m_prepaid_id_counter;
};

class Postpaid_customer : public Customer {
 public:
  Postpaid_customer(const std::string& name, const std::string& mob_number,
                    const uint32_t call_duration, const uint32_t balance,
                    Customer_type type);
  ~Postpaid_customer();

  bool credit(uint32_t amount) override;

 private:
  bool bill_pay(uint32_t);
  /*
        At the moment this will always be a simple integer counter.
        We may improve it in following two ways :
        -  by making it alpanumeric counter
        -  by reusing the old ids
  */
  static uint64_t m_postpaid_id_counter;
};

/*
  Abstract class for Mobile_billing system.
  The concrete instances are responsible for providing the functionality of
  prepaid or postpaid billing system.
*/
class Mobile_billing {
 public:
  /*
    Factory Method to create the Mobile Billing system
  */
  static std::unique_ptr<Mobile_billing> create(Customer_type type,
                                                uint32_t pulse_rate);
  virtual ~Mobile_billing();

  // Prohibit the Copy and assignment operations
  Mobile_billing(const Mobile_billing&) = delete;
  Mobile_billing(Mobile_billing&&) = delete;
  Mobile_billing& operator=(const Mobile_billing&) = delete;
  Mobile_billing& operator=(Mobile_billing&&) = delete;

  /*
    Register the customer to the mobile_billing system
	@param
    name			[in]	Name of the customer
    mob_number		[in]	Mobile number of the customer
    call_duration	[in]	Call duration allowed for the customer.
                            For prepaid customers it should be 0
	initial_amount	[in]	Initial amount given by the  customer
  */
  virtual void add_customer(const std::string& name,
                            const std::string& mob_number,
                            const uint32_t call_duration,
                            const uint32_t initial_amount) = 0;

  /*
    We can have other methods to support deleting customers with other
    criteria as well. But not adding them right now due to lack of time.
  */
  virtual void delete_customer_by_mob_number(const std::string& mob_number) = 0;
  virtual Customer* search_by_Id(const uint64_t Id) = 0;

  Customer* search_by_name(const std::string& name);
  Customer* search_by_number(const std::string& number);

  // Will always be positive integer
  uint32_t get_average_post_paid_call_duration();
  uint32_t get_average_pre_paid_balance();

 protected:
  Mobile_billing(uint32_t pulse_rate);

  std::vector<std::unique_ptr<Customer>> m_customers;
  std::map<const uint64_t, Customer*> m_id_map;
  std::map<const std::string, Customer*> m_name_map;
  std::map<const std::string, Customer*> m_mob_num_map;
  uint32_t m_pulse_rate;
  uint32_t m_avg_balance;
  uint32_t m_avg_call_duration;
};

class Mobile_billing_postpaid : public Mobile_billing {
 public:
  Mobile_billing_postpaid(uint32_t pulse_rate);
  void add_customer(const std::string& name, const std::string& mob_number,
                    const uint32_t call_duration,
                    const uint32_t initial_amount) override;
  void delete_customer_by_mob_number(const std::string& mob_number) override;
  Customer* search_by_Id(const uint64_t Id) override;
};

class Mobile_billing_prepaid : public Mobile_billing {
 public:
  Mobile_billing_prepaid(uint32_t pulse_rate);
  void add_customer(const std::string& name, const std::string& mob_number,
                    const uint32_t call_duration,
                    const uint32_t initial_amount) override;
  void delete_customer_by_mob_number(const std::string& mob_number) override;
  Customer* search_by_Id(const uint64_t Id) override;
};

#endif /* MOBILE_BANKLING_INCLUDED*/
