require 'db_core/models/model'

class CheckInDesk < Model
  def CheckInDesk.create_table(connection)
    begin
      connection.do("
CREATE TABLE check_in_desks(
    id serial PRIMARY KEY,
    name varchar(16) UNIQUE NOT NULL,
    description text
) WITH OIDS
        ")
      return true
    rescue DBI::ProgrammingError => e
      return false
    end
  end
  def CheckInDesk.find_all_by_id(connection, id)
    query = []
    res = []
    query = ["SELECT * FROM check_in_desks WHERE id = ?", id]
    connection.select_all(*query) do |r|
      o = self.new
      r.column_names.each do |c|
        o[c.to_sym] = r[c]
      end
      res << o
    end
    return res
  end
end
