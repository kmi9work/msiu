require 'db_core/models/model'

class Terminal < Model
  def Terminal.create_table(connection)
    begin
      connection.do("
CREATE TABLE terminals(
  id serial PRIMARY KEY,
  name varchar(8) UNIQUE NOT NULL,
  description text,
  needs_bus boolean NOT NULL DEFAULT false
) WITH OIDS
        ")
      return true
    rescue DBI::ProgrammingError => e
      return false
    end
  end
=begin
  def Terminal.find_by_id(connection, id)
    query = []
    res = []
    query = ["SELECT * FROM terminals WHERE id = ?", id]
    connection.select_all(*query) do |r|
      o = self.new
      r.column_names.each do |c|
        o[c.to_sym] = r[c]
      end
      res << o
    end
    return res
  end
=end
end
