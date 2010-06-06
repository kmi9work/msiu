require 'db_core/db_driver'

# Подключает все файлы db_core/model/*.rb
Dir[File.join(File.dirname(__FILE__), 'models', "*.rb")].each do |f|
  require(f)
end

class CreateDatabase
  # Используемые модели
  MODELS = [Terminal, CheckInDesk, Company, Flight, 
    CheckInDeskFlight, FlightTerminal, FlightStatus, User, FlyPersonal, Crew]
  CREATE_OK = 1 + MODELS.size

  def initialize()
  end

  # Создание пустой БД и всех таблиц. Внимание! БД сначала удаляется!
  def create
    creation_counter = 0
    @db_empty = DbDriver.empty_connection()
    creation_counter += self.drop_db()
    creation_counter += self.create_db()
    creation_counter += self.create_tables()
    @db_empty.disconnect()
    return creation_counter
  end

  # Создание пустой БД
  def create_db()
    begin
      @db_empty.do("CREATE DATABASE aero")
      return 1
    rescue DBI::ProgrammingError => e
      return 0
    end
  end

  # Удаление БД
  def drop_db()
    begin
      @db_empty.do("DROP DATABASE aero")
      return 1
    rescue DBI::ProgrammingError => e
      return 0
    end
  end

  # См. константу MODELS
  def models()
    MODELS
  end

  # Создание всех таблиц
  def create_tables()
    creation_counter = 0
    db = DbDriver.instance()
    self.models.each do |cls|
      creation_counter += 1 if cls.create_table(db)
    end
    DbDriver.close()
    return creation_counter
  end

  # Тестовое добавление данных
  def insert_test_data()
    db = DbDriver.instance()
    c = Company.new
    c[:name] = 'Сибирь'
    c[:code] = 'SB'
    c[:description] = 'Авиакомпания "Сибирь" - Россия'
    c.save(db)
    
    c1 = Company.new
    c1[:name] = 'Eastline'
    c1[:code] = 'DIE'
    c1[:description] = 'Хочешь в рабство?'
    c1.save(db)
    
    f = Flight.new
    f[:code] = (c[:code] + '00001')
    f[:arrival_date] = '2009-10-10 10:00:00'
    f[:departure_date] = '2009-10-10 22:00:00'
    f[:arrival_place] = 'Лондон'
    f[:departure_place] = 'Москва'
    f[:arrival_airport] = 'Хитроу'
    f[:departure_airport] = 'Внуково'
    f[:is_departure] = true
    f[:company_id] = c[:id]
    f.save(db)
    
    f = Flight.new
    f[:code] = (c[:code] + '00002')
    f[:arrival_date] = '2010-10-10 10:00:00'
    f[:departure_date] = '2010-10-10 22:00:00'
    f[:arrival_place] = 'Таймыр'
    f[:departure_place] = 'Москва'
    f[:arrival_airport] = 'Таймыр-1'
    f[:departure_airport] = 'Внуково'
    f[:is_departure] = false
    f[:company_id] = c[:id]
    f.save(db)
    
    f = Flight.new
    f[:code] = (c1[:code] + '00001')
    f[:arrival_date] = '2012-10-10 10:00:00'
    f[:departure_date] = '2012-10-10 22:00:00'
    f[:arrival_place] = 'Дудинка'
    f[:departure_place] = 'Москва'
    f[:arrival_airport] = 'Дудинковский основной эропорт'
    f[:departure_airport] = 'Домодедово'
    f[:is_departure] = true
    f[:company_id] = c1[:id]
    f.save(db)
    
    checkindesk = CheckInDesk.new({
      :name => 'ch1',
      :description => 'ch1desk'
    })
    checkindesk.save(db)
    checkindesk = CheckInDesk.new({
      :name => 'ch2',
      :description => 'ch2desk'
    })
    checkindesk.save(db)
    checkindeskflight = CheckInDeskFlight.new({
      :flight_id => 1,
      :check_in_desk_id => 1,
      :info => 'cidf_info1'
    })
    checkindeskflight.save(db)
    checkindeskflight = CheckInDeskFlight.new({
      :flight_id => 2,
      :check_in_desk_id => 2,
      :info => 'cidf_info2'
    })
    checkindeskflight.save(db)
    
    flightstatus = FlightStatus.new({
      :flight_id => 1,
      :status_id => 1,
      :event_date => Time.new.strftime("%Y.%m.%d %H:%M")
    })
    flightstatus.save(db)
    
    flightstatus = FlightStatus.new({
      :flight_id => 1,
      :status_id => 2,
      :event_date => (Time.new + 3600).strftime("%Y.%m.%d %H:%M")
    })
    flightstatus.save(db)
    
    flightstatus = FlightStatus.new({
      :flight_id => 2,
      :status_id => 1,
      :event_date => (Time.new - 3600).strftime("%Y.%m.%d %H:%M")
    })
    flightstatus.save(db)
    
    terminal = Terminal.new({
      :name => 'T1',
      :description => 'Terminal1 info',
      :needs_bus => true
    })
    terminal.save(db)
    
    terminal = Terminal.new({
      :name => 'T2',
      :description => 'Terminal2 info',
      :needs_bus => false
    })
    terminal.save(db)
    
    flightterminal = FlightTerminal.new({
      :flight_id => 1,
      :terminal_id => 1,
      :info => 'Terminal1f1'
    })
    flightterminal.save(db)
    
    flightterminal = FlightTerminal.new({
      :flight_id => 2,
      :terminal_id => 2,
      :info => 'Terminal2f2'
    })
    flightterminal.save(db)
    
    flypersonal = FlyPersonal.new({
      :first_name => 'Андрей',
      :second_name => 'Чевелёв',
      :patronymic_name => 'Сергеевич',
      :age => 18, 
      :job_title => 1
    })
    flypersonal.save(db)
    
    flypersonal = FlyPersonal.new({
      :first_name => 'Наталья',
      :second_name => 'Лукьянова',
      :patronymic_name => 'Владимировна',
      :age => 17, 
      :job_title => 0 
    })
    flypersonal.save(db)

    flypersonal = FlyPersonal.new({
      :first_name => 'Михаил',
      :second_name => 'Костенчук',
      :patronymic_name => 'Ильич',
      :age => 21, 
      :job_title => 2
    })
    flypersonal.save(db)
    
    flypersonal = FlyPersonal.new({
      :first_name => 'Марат',
      :second_name => 'Нафиков',
      :patronymic_name => 'Артурович',
      :age => 19, 
      :job_title => 1
    })
    flypersonal.save(db)
    
    flypersonal = FlyPersonal.new({
      :first_name => 'Ирина',
      :second_name => 'Вернер',
      :patronymic_name => 'Алексеевна',
      :age => 19, 
      :job_title => 0
    })
    flypersonal.save(db)
    
    flypersonal = FlyPersonal.new({
      :first_name => 'Лёха',
      :second_name => 'Юдин',
      :patronymic_name => 'Англичанин',
      :age => 17, 
      :job_title => 3
    })
    flypersonal.save(db)
      
    flypersonal = FlyPersonal.new({
      :first_name => 'Асланбек',
      :second_name => 'Абазов',
      :patronymic_name => 'Эдуардович',
      :age => 13, 
      :job_title => 2
    })
    flypersonal.save(db)
    DbDriver.close()
  end
end
