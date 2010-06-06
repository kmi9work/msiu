count = 0
"
<table class = 'list'>
  <caption>
      #{@header}
  </caption>

  <thead>
    <tr>
      <th>
        Должность
      </th>
      <th>
        ФИО
      </th>
      <th>
        Возраст
      </th>
    </tr>
  </thead>
  <tbody>
" + @items.map do |i|
      count += 1
"
    <tr class = 'list#{count % 2}'>
      <td>#{i[:job_title]}</td>
      <td>#{i[:first_name]}, #{i[:second_name]} #{i[:patronymic_name]}</td>
      <td>#{i[:age]}</td>
    </tr>
"
end.join("\n") + "
  </tbody>
</table>
"
