// Mobile_banking.cpp :

#include "mobile_banking.h"
#include <algorithm>
#include <cassert>
#include <iostream>

// Initialize static ID trackers
uint64_t Prepaid_customer::m_prepaid_id_counter = 1;
uint64_t Postpaid_customer::m_postpaid_id_counter = 1;

std::unique_ptr<Customer> Customer::create(const std::string& name,
                                           const std::string& mob_number,
                                           const uint32_t call_duration,
                                           const uint32_t balance,
                                           Customer_type type) {
  std::unique_ptr<Customer> customer(nullptr);
  switch (type) {
    case Customer_type::Pre_paid:
      customer = std::make_unique<Prepaid_customer>(
          name, mob_number, call_duration, balance, type);
      break;
    case Customer_type::Post_paid:
      customer = std::make_unique<Postpaid_customer>(
          name, mob_number, call_duration, balance, type);
      break;
    default:
      break;
  }
  return customer;
}

Customer::Customer(const std::string& name, const std::string& mob_number,
                   const uint32_t call_duration, const uint32_t balance,
                   Customer_type type)
    : m_name(name),
      m_mob_number(mob_number),
      m_call_duration(call_duration),
      m_balance(balance),
      m_type(type) {}

Customer::~Customer() {}

uint64_t Customer::get_id() { return m_customer_id; }

Customer_type Customer::get_type() { return m_type; }

std::string Customer::get_mob_number() { return m_mob_number; }

std::string Customer::get_name() { return m_name; }

uint32_t Customer::enquire_balance() { return m_balance; }

uint32_t Customer::enquire_call_duration() { return m_call_duration; }

// Print the Customer's details to the output stream
std::ostream& operator<<(std::ostream& os, const Customer& customer) {
  os << "Customer Id : " << customer.m_customer_id
     << ", Name : " << customer.m_name
     << ", Mobile Number : " << customer.m_mob_number << ", Type : "
     << (customer.m_type == Customer_type::Pre_paid ? " Prepaid "
                                                    : " Postpaid ")
     << ", Average balance : " << customer.m_balance
     << ",  Average Call duration " << customer.m_call_duration << std::endl;
  return os;
}

Prepaid_customer::Prepaid_customer(const std::string& name,
                                   const std::string& mob_number,
                                   const uint32_t call_duration,
                                   const uint32_t balance, Customer_type type)
    : Customer(name, mob_number, call_duration, balance, type) {
  m_customer_id = m_prepaid_id_counter++;
}

Prepaid_customer::~Prepaid_customer() {}

bool Prepaid_customer::credit(uint32_t amount) { return recharge(amount); }

/*
  assuming the amount specified is valid
*/
bool Prepaid_customer::recharge(uint32_t amount) {
  m_balance += amount;
  return true;
}

Postpaid_customer::Postpaid_customer(const std::string& name,
                                     const std::string& mob_number,
                                     const uint32_t call_duration,
                                     const uint32_t balance, Customer_type type)
    : Customer(name, mob_number, call_duration, balance, type) {
  m_customer_id = m_postpaid_id_counter++;
}

Postpaid_customer::~Postpaid_customer() {}

bool Postpaid_customer::credit(uint32_t amount) { return bill_pay(amount); }

/*
  Assuming the input amount will be valid positive number.
  We calculate the current balance and resets the call duration.
  Note - For now now not handling the validation of bill payment.

  @param
        amount [in] amount to be paid
  @retval:
        true : Bill paid successfully
        false : Bill could not be paid
*/
bool Postpaid_customer::bill_pay(uint32_t amount) {
  m_balance = (m_balance + amount) - m_call_duration;
  m_call_duration = 0;
  return true;
}

std::unique_ptr<Mobile_billing> Mobile_billing::create(Customer_type type,
                                                       uint32_t pulse_rate) {
  std::unique_ptr<Mobile_billing> mb = nullptr;
  switch (type) {
    case Customer_type::Pre_paid:
      mb = std::make_unique<Mobile_billing_prepaid>(pulse_rate);
      break;
    case Customer_type::Post_paid:
      mb = std::make_unique<Mobile_billing_postpaid>(pulse_rate);
      break;
    default:
      break;
  }
  return mb;
}

Mobile_billing::Mobile_billing(uint32_t pulse_rate)
    : m_pulse_rate(pulse_rate) {}

Mobile_billing::~Mobile_billing() {}

Mobile_billing_prepaid::Mobile_billing_prepaid(uint32_t pulse_rate)
    : Mobile_billing(pulse_rate) {}

void Mobile_billing_prepaid::add_customer(const std::string& name,
                                          const std::string& mob_number,
                                          const uint32_t call_duration,
                                          const uint32_t balance) {
  /*
    We must validate the arguments name, mob_number, call duration and throw
        exception for invalid type. For now assuming that values are unique.
  */
  std::unique_ptr<Customer> customer = Customer::create(
      name, mob_number, call_duration, balance, Customer_type::Pre_paid);
  m_name_map.emplace(name, customer.get());
  m_mob_num_map.emplace(mob_number, customer.get());

  m_avg_balance =
      ((m_id_map.size() * m_avg_balance + balance) / (m_id_map.size() + 1));
  m_id_map.emplace(customer->get_id(), customer.get());

  m_customers.emplace_back(std::move(customer));
}

void Mobile_billing_prepaid::delete_customer_by_mob_number(
    const std::string& mob_number) {
  auto cust = m_mob_num_map.find(mob_number);
  if (cust != m_mob_num_map.end()) {
    m_avg_balance =
        ((m_avg_balance * m_id_map.size()) - cust->second->enquire_balance()) /
        (m_id_map.size() - 1);
    m_id_map.erase(cust->second->get_id());
    m_name_map.erase(cust->second->get_name());
  }
  // Find the customer info in the array and remove that.
  auto it = find_if(m_customers.begin(), m_customers.end(),
                    [&](auto& obj) { return obj.get() == cust->second; });
  if (it != m_customers.end()) {
    auto retval = std::move(*it);
    m_customers.erase(it);
  }
}

Customer* Mobile_billing_prepaid::search_by_Id(const uint64_t Id) {
  Customer* customer = nullptr;
  auto itr = m_id_map.find(Id);
  if (itr != m_id_map.end()) {
    customer = itr->second;
  }
  return customer;
}

Mobile_billing_postpaid::Mobile_billing_postpaid(uint32_t pulse_rate)
    : Mobile_billing(pulse_rate) {}

void Mobile_billing_postpaid::add_customer(const std::string& name,
                                           const std::string& mob_number,
                                           const uint32_t call_duration,
                                           const uint32_t balance) {
  /*
    We must validate the arguments name, mob_number, call duration and throw
    exception for invalid type. For now assuming that values are valid.
  */
  std::unique_ptr<Customer> customer = Customer::create(
      name, mob_number, call_duration, balance, Customer_type::Post_paid);

  m_name_map.emplace(name, customer.get());
  m_mob_num_map.emplace(mob_number, customer.get());

  m_avg_call_duration =
      ((m_id_map.size() * m_avg_call_duration + call_duration) /
       (m_id_map.size() + 1));
  m_id_map.emplace(customer->get_id(), customer.get());
  m_customers.emplace_back(std::move(customer));
}

void Mobile_billing_postpaid::delete_customer_by_mob_number(
    const std::string& mob_number) {
  auto cust = m_mob_num_map.find(mob_number);
  if (cust != m_mob_num_map.end()) {
    m_avg_call_duration = ((m_avg_call_duration * m_id_map.size()) -
                           cust->second->enquire_call_duration()) /
                          (m_id_map.size() - 1);
    m_id_map.erase(cust->second->get_id());
    m_name_map.erase(cust->second->get_name());
  }
  // Find the customer info in the array and remove that.
  auto it = find_if(m_customers.begin(), m_customers.end(),
                    [&](auto& obj) { return obj.get() == cust->second; });
  if (it != m_customers.end()) {
    auto retval = std::move(*it);
    m_customers.erase(it);
  }
}

Customer* Mobile_billing_postpaid::search_by_Id(const uint64_t Id) {
  Customer* customer = nullptr;
  auto itr = m_id_map.find(Id);
  if (itr != m_id_map.end()) {
    customer = itr->second;
  }
  return customer;
}

Customer* Mobile_billing::search_by_name(const std::string& name) {
  Customer* customer = nullptr;
  auto itr = m_name_map.find(name);
  if (itr != m_name_map.end()) {
    customer = itr->second;
  }
  return customer;
}
Customer* Mobile_billing::search_by_number(const std::string& number) {
  Customer* customer = nullptr;
  auto itr = m_mob_num_map.find(number);
  if (itr != m_mob_num_map.end()) {
    customer = itr->second;
  }
  return customer;
}

// Will always be positive integer
uint32_t Mobile_billing::get_average_post_paid_call_duration() {
  return m_avg_call_duration;
}

// Will always be positive integer
uint32_t Mobile_billing::get_average_pre_paid_balance() {
  return m_avg_balance;
}

int main() {
  std::unique_ptr<Mobile_billing> prepaid_mb =
      Mobile_billing::create(Customer_type::Pre_paid, 1);
  std::unique_ptr<Mobile_billing> postpaid_mb =
      Mobile_billing::create(Customer_type::Post_paid, 2);
  if (prepaid_mb) {
    prepaid_mb->add_customer("cs", "9900114192", 0, 1000);
    prepaid_mb->add_customer("ds", "9900114193", 0, 500);
    std::cout << prepaid_mb->get_average_pre_paid_balance() << std::endl;
    prepaid_mb->delete_customer_by_mob_number("9900114193");
    std::cout << "After removing thecustomer" << std::endl;
    std::cout << prepaid_mb->get_average_pre_paid_balance() << std::endl;
    Customer* cs = prepaid_mb->search_by_number("9900114192");
    if (cs) std::cout << *cs;
  }
  if (postpaid_mb) {
    postpaid_mb->add_customer("as", "9900114190", 400, 0);
    postpaid_mb->add_customer("bs", "9900114191", 500, 0);
    std::cout << postpaid_mb->get_average_post_paid_call_duration()
              << std::endl;
    postpaid_mb->delete_customer_by_mob_number("9900114191");
    std::cout << "After removing thecustomer" << std::endl;
    std::cout << postpaid_mb->get_average_post_paid_call_duration()
              << std::endl;
    Customer* cs = postpaid_mb->search_by_number("9900114190");
    if (cs) std::cout << *cs;
  }

  return 0;
}
