$:.unshift File.join(File.dirname(__FILE__),'..','lib')

require 'test/unit'
require 'db_core/create_database'

class TestCreateDatabase < Test::Unit::TestCase
  def test_creation
    creator = CreateDatabase.new
    assert(creator.create() >= CreateDatabase::CREATE_OK,
      'Процесс создания пустой БД не может завершиться успешно!')
  end
  
  def test_insert_test_data()
    creator = CreateDatabase.new
    creator.insert_test_data()
    db = DbDriver.instance
    res = db.select_one("SELECT count(*) FROM flights")
    assert(res[0].to_i == 1, 'Тестовые данные внесены успешно!')
    User.create_admin(db)
    assert(User.check_user(db, 'admin', 'qwerty'), 'Ошибка добавления администратора!')
    DbDriver.close()
  end

  def test_models()
    db = DbDriver.instance
    #Company=======================================
    cs = Company.find_all(db)
    assert(cs.size == 1, 'Не работает find_all для модели Company!')
    company = Company.new({
      :name => "lol",
      :code => 123,
      :description => "best"    
    })
    company.save(db)
    company = Company.new({
      :name => "lol1",
      :code => 222,
      :description => "best"    
    })
    company.save(db)
    
    assert(Company.find_all(db).size == 3, 'Не работает find_all для модели Company!')
    #Flight=======================================
    flight = Flight.new({
      :code => 123,
      :arrival_date => "2009.05.31 14:05",
      :departure_date => "2010.05.31 14:05",
      :arrival_place => "aplace1",
      :departure_place => "dplace1",
      :arrival_airport => "aair1",
      :departure_airport => "dair1",
      :company_id => 1,
      :is_departure => true
    })
    flight.save(db)
    flight = Flight.new({
      :code => 333,
      :arrival_date => "2009.05.31 14:05",
      :departure_date => "2010.05.31 14:05",
      :arrival_place => "aplace2",
      :departure_place => "dplace2",
      :arrival_airport => "aair2",
      :departure_airport => "dair2",
      :company_id => 2,
      :is_departure => false
    })
    flight.save(db)
    
    assert(Flight.find_all(db).size == 3, 'Не работает find_all для модели Flight!')

    #CheckInDesk find all======================================="
    checkindesk = CheckInDesk.new({
      :name => "cid1",
      :description => "descCid1"
    })
    checkindesk.save(db)
    checkindesk = CheckInDesk.new({
      :name => "cid2",
      :description => "descCid2"
    })
    checkindesk.save(db)
    
    assert(CheckInDesk.find_all(db).size == 2, 'Не работает find_all для модели CheckInDesk!')
    #CheckInDesk Flight find all======================================="
    
    flightcheckindesk = FlightCheckInDesk.new({
      :flight_id => 1,
      :check_in_desk_id => 1,
      :info => "cid_f1"
    })
    flightcheckindesk.save(db)
    flightcheckindesk = FlightCheckInDesk.new({
      :flight_id => 1,
      :check_in_desk_id => 2,
      :info => "cid_f2"
    })
    flightcheckindesk.save(db)
    assert(FlightCheckInDesk.find_by_id(db, 1).check_in_desk[:name] == 'cid1', 'Не работает Find_by_id  в FlightCheckInDesk')
    assert(FlightCheckInDesk.find_all(db).size == 2, 'Не работает find_all для модели FlightCheckInDesk!')
    
    #FlightStatus find all======================================="
    
    flightstatus = FlightStatus.new({
      :flight_id => 1,
      :status => 1,
      :event_date => Time.new.strftime("%Y.%m.%d %H:%M"),
    })
    flightstatus.save(db)
    
    flightstatus = FlightStatus.new({
      :flight_id => 1,
      :status => 2,
      :event_date => (Time.new + 300).strftime("%Y.%m.%d %H:%M"),
    })
    flightstatus.save(db)
    
    flightstatus = FlightStatus.new({
      :flight_id => 1,
      :status => 3,
      :event_date => (Time.new + 3600).strftime("%Y.%m.%d %H:%M"),
    })
    flightstatus.save(db)
    
    flightstatus = FlightStatus.new({
      :flight_id => 2,
      :status => 3,
      :event_date => Time.new.strftime("%Y.%m.%d %H:%M"),
    })
    flightstatus.save(db)
    assert(FlightStatus.find_all(db).size == 4, 'Не работает find_all для модели FlightStatus!')
    
    #===================="
    assert(FlightStatus.find_all_by_flight_id(db, 2).size == 1, 'Не работает find_all_by_flight_id 2 для модели FlightStatus!')
    assert(FlightStatus.find_all_by_flight_id(db, 1).size == 3, 'Не работает find_all_by_flight_id 1 для модели FlightStatus!')
    
    
    
    
    #Terminal ======================================="
    
    terminal = Terminal.new({
      :name => "firstT",
      :description => "best Terminal",
      :needs_bus => true
    })
    terminal.save(db)
    
    terminal = Terminal.new({
      :name => "secondT",
      :description => "best of the best Terminal2",
      :needs_bus => false
    })
    terminal.save(db)
    
    assert(Terminal.find_all(db).size == 2, 'Не работает find_all для модели Terminal!')
    
    #FlightTerminal ======================================="
    flightterminal = FlightTerminal.new({
      :flight_id => 1,
      :terminal_id => 2,
      :info => "ft1"
    })
    flightterminal.save(db)
    flightterminal = FlightTerminal.new({
      :flight_id => 1,
      :terminal_id => 1,
      :info => "ft2"
    })
    flightterminal.save(db)
    assert(FlightTerminal.find_all(db).size == 2, 'Не работает find_all для модели FlightTerminal!')
    
    puts "================"
    puts FlightTerminal.find_all_by_flight_id(db, 1).map{|i| i.terminal[:name]}
    puts FlightTerminal.find_by_id(db, 1)[:info]
    #test Flights all=======
    
    #User==========
    superuser = User.new({
      :login => "su1",
      :password => "sp1",
      :info => "si1",
      :is_super => true
    })
    superuser.save(db)
    easyuser = User.new({
      :login => "eu1",
      :password => "ep1",
      :info => "ei1",
      :is_super => false
    })
    easyuser.save(db)
    user = User.new({
      :login => "u1",
      :password => "p3",
      :info => "i3",
      :is_super => false
    })
    user.save(db)
    easyuser = User.new({
      :login => "eu2",
      :password => "ep2",
      :info => "su1",
      :is_super => false
    })
    easyuser.save(db)
    usearch = User.search(db, 'su1')
    
    assert((usearch[0][0].to_s == "Super user | su1 | si1" and usearch[0][1] == 0), 'Search don\'t working')
    assert((usearch[1][0].to_s == "Easy user | eu2 | su1" and usearch[1][1] == 1), 'Search don\'t working')
    #assert(!fs[0].company.nil?, 'Не находятся связанные объекты!')
    DbDriver.close()
  end
end
