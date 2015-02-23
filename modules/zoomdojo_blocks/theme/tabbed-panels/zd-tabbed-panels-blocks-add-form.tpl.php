<form method="POST" id="form-tabbbled-block">
    <div class="show-children <?php print ($bundle=='node')?'hide':''; ?>">
        <h3>Show-children:</h3>
        <div>
            <label>
                <?php if($show): ?>
                    <input type="checkbox" name="children" value="1" id="children" checked="checked" /><span>Yes</span>
                <?php else: ?>
                    <input type="checkbox" name="children" value="0" id="children" /><span>No</span>
                <?php endif; ?>
            </label>
        </div>
    </div>
    <div id="dialog" title="Select category">
        <select id="select-category">
            <?php foreach ($allCategories as $category): ?>
                <option value="<?php print $category->id; ?>"><?php print $category->title; ?> (<?php print $category->language; ?>)</option>
            <?php endforeach; ?>
        </select>
    </div>
     
    <a href="#" class="button" id="add_tab">Add category</a>
     
    <div id="tabs">
        <ul>
            <?php foreach ($categories as $category): ?>
                <li>
                    <a href="#tabs-<?php print $category->id; ?>"><?php print $category->title; ?> (<?php print $category->language; ?>)</a>
                    <span class="ui-icon ui-icon-close" role="presentation">Remove Tab</span>
                </li>
            <?php endforeach; ?>
        </ul>
        <?php foreach ($categories as $category): ?>
            <div id="tabs-<?php print $category->id; ?>">
                <div class="add-item">
                    <a href="#" data-cid="<?php print $category->id; ?>" class="add-item-btn button">Add item</a>
                </div>
                <div class="row">
                    <label>Title:</label>
                    <input type="text" name="title[<?php print $category->id; ?>][]" value=""/>
                    <label>Url:</label>
                    <input type="text" name="url[<?php print $category->id; ?>][]" value=""/>
                    <label>New window:</label>
                    <input type="checkbox" class="nw" name="nw[<?php print $category->id; ?>][]" checked="checked" value="1"/>
                </div>
            </div>
        <?php endforeach; ?>
    </div>
    <div class="submit-btn">
        <input type="hidden" name="bundle" id="form-bundle" value="<?php print $bundle; ?>" />
        <input type="hidden" name="type" id="form-type" value="add" />
        <input type="hidden" name="entity" id="form-entity" value="<?php print $entityId; ?>" />
        <input type="hidden" name="show" id="form-show" value="0" />
        <a href="#" class="button" id="submit-form">Save</a>
    </div>
</form>

<script type="text/x-template" id="tab-new-content">
    <div class="add-item">
        <a href="#" data-cid="<%= cid %>" class="add-item-btn button">Add item</a>
    </div>
    <div class="row">
        <label>Title:</label>
        <input type="text" name="title[<%= cid %>][]" value=""/>
        <label>Url:</label>
        <input type="text" name="url[<%= cid %>][]" value=""/>
        <label>New window:</label>
        <input type="checkbox" class="nw" name="nw[<%= cid %>][]" checked="checked" value="1"/>
    </div>
</script>

<script type="text/x-template" id="tab-new-row">
    <div class="row">
        <div class="inputs-left">
            <label>Title:</label>
            <input type="text" name="title[<%= cid %>][]" value=""/>
            <label>Url:</label>
            <input type="text" name="url[<%= cid %>][]" value=""/>
            <label>New window:</label>
            <input type="checkbox" class="nw" name="nw[<%= cid %>][]" checked="checked" value="1"/>
        </div>
        <div class="delete-current-row"></div>
    </div>
</script>
