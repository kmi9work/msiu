count = 0
"
<form name = 'aero' action = 'aero.rb' method = 'post'>
  <input type = 'hidden' name = 'controller' value = 'User'>
  <input type = 'hidden' name = 'action' value = 'search'>
  <input type = 'hidden' name = 'is_commit' value = 'true'>
  Поиск: <input type='text' name='item[search]' value=''> <input type = 'submit' value = 'Найти'><br>
</form>
<br>
<table class = 'list'>
  <thead>
    <tr>
      <th>
        Совпадение
      </th>
      <th>
        Колонка
      </th>
    </tr>
  </thead>
  <tbody>
" +  
  if @items 
    @items.map do |item|
      count += 1
"
    <tr class = 'list#{count % 2}'>
      <td>#{item[0].to_s}</td>
      <td>#{User::USER_COLUMNS[item[1]]}</td>
    </tr>
"
    end.join("\n")
  else
    ''
  end + "
  </tbody>
</table>
"