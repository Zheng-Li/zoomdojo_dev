<div id="items-wrapper" class="veteran-st-admin-wrapper">
    <form method="POST" id="send-items-data-form">
        <div id="tabs">
            <ul>
                <?php foreach ($categories as $category): ?>
                    <li>
                        <a href="#tabs-<?php print $category->id; ?>"><?php print $category->title; ?></a>
                        <span class="ui-icon ui-icon-close" role="presentation">Remove Tab</span>
                    </li>
                <?php endforeach; ?>
            </ul>
            <?php foreach ($categories as $category): ?>
                <div id="tabs-<?php print $category->id; ?>">
                    <div class="add-item">
                        <a href="#" data-cid="<?php print $category->id; ?>" class="add-item-btn button">Add item</a>
                    </div>
                    <?php if (!empty($items)): ?>
                        <table class="table-items" id="tabs-table-<?php print $category->id; ?>">
                            <thead>
                                <tr>
                                    <?php foreach ($category->fields as $field): ?>
                                        <th><?php print $field->name; ?> (<?php print $field->type; ?>)</th>
                                    <?php endforeach; ?>
                                    <th>Delete</th>
                                </tr>
                            </thead>
                            <tbody>
                                <?php if (!empty($items[$category->id])): ?>
                                    <?php foreach($items[$category->id] as $item): ?>
                                        <tr>
                                            <?php foreach ($category->fields as $k => $field): ?>
                                                <td><input type="text" class="input-field-veteran-st" name="field<?php print $k; ?>[<?php print $category->id; ?>][]" value="<?php $f = 'field'.$k; print $item->$f; ?>" /></td>
                                            <?php endforeach; ?>
                                            <td>
                                                <div class="delete-current-row"></div>
                                                <input type="hidden" name="weight[<?php print $category->id; ?>][]" class="weight-input" value="<?php print $item->weight; ?>" />
                                                <input type="hidden" name="id[<?php print $category->id; ?>][]" value="<?php print $item->id; ?>" />
                                            </td>
                                        </tr>
                                    <?php endforeach; ?>
                                <?php else: ?>
                                    <tr>
                                        <?php foreach ($category->fields as $k => $field): ?>
                                            <td><input type="text" class="input-field-veteran-st" name="field<?php print $k; ?>[<?php print $category->id; ?>][]" /></td>
                                        <?php endforeach; ?>
                                        <td>
                                            <div class="delete-current-row"></div>
                                            <input type="hidden" name="weight[<?php print $category->id; ?>][]" class="weight-input" value="0" />
                                            <input type="hidden" name="id[<?php print $category->id; ?>][]" value="0" />
                                        </td>
                                    </tr>
                                <?php endif; ?>
                            </tbody>
                        </table>
                    <?php else: ?>
                        <table class="table-items" id="tabs-table-<?php print $category->id; ?>">
                            <thead>
                                <tr>
                                    <?php foreach ($category->fields as $field): ?>
                                        <th><?php print $field->name; ?> (<?php print $field->type; ?>)</th>
                                    <?php endforeach; ?>
                                    <th>Delete</th>
                                </tr>
                            </thead>
                            <tbody>
                                <tr>
                                    <?php foreach ($category->fields as $k => $field): ?>
                                        <td><input type="text" class="input-field-veteran-st" name="field<?php print $k; ?>[<?php print $category->id; ?>][]" /></td>
                                    <?php endforeach; ?>
                                    <td>
                                        <div class="delete-current-row"></div>
                                        <input type="hidden" name="weight[<?php print $category->id; ?>][]" class="weight-input" value="0" />
                                        <input type="hidden" name="id[<?php print $category->id; ?>][]" value="0" />
                                    </td>
                                </tr>
                            </tbody>
                        </table>
                    <?php endif; ?>
                </div>
            <?php endforeach; ?>
        </div>
        <div class="submit-btn">
            <input type="hidden" name="save" value="0" />
            <a href="#" class="button" id="submit-form">Save</a>
            <a href="/admin/zoomdojo/items-block/blocks" class="button">Cancel</a>
        </div>
    </form>
</div>

<script type="text/x-template" id="tab-new-row">
    <tr>
        <?php for ($i = 0; $i < 4; $i++): ?>
            <td><input type="text" class="input-field-veteran-st" name="field<?php print $i; ?>[<%= cid %>][]" /></td>
        <?php endfor; ?>
        <td>
            <div class="delete-current-row"></div>
            <input type="hidden" name="weight[<%= cid %>][]" class="weight-input" value="<%= weight %>" />
            <input type="hidden" name="id[<%= cid %>][]" value="0" />
        </td>
    </tr>
</script>
