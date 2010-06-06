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
    assert(res[0].to_i == 3, 'Тестовые данные внесены не успешно!')
    User.create_admin(db)
    assert(User.check_user(db, 'admin', 'qwerty'), 'Ошибка добавления администратора!')
    DbDriver.close()
  end

  def test_models()
    db = DbDriver.instance
    assert(Company.find_all(db).size == 2, 'Не работает find_all для модели Company!')
    assert(Flight.find_all(db).size == 3, 'Не работает find_all для модели Flight!')    
    assert(CheckInDesk.find_all(db).size == 2, 'Не работает find_all для модели CheckInDesk!')    
    assert(CheckInDeskFlight.find_all(db).size == 2, 'Не работает find_all для модели CheckInDeskFlight!')
    assert(FlightStatus.find_all(db).size == 3, 'Не работает find_all для модели FlightStatus!')    
    assert(Terminal.find_all(db).size == 2, 'Не работает find_all для модели Terminal!')
    assert(FlightTerminal.find_all(db).size == 2, 'Не работает find_all для модели FlightTerminal!')
    assert(FlyPersonal.find_all(db).size == 7, 'Не работает find_all для модели FlyPersonal!')
    p FlyPersonal.find_all_by_job_id(db, 0) 
    DbDriver.close()
  end
end
